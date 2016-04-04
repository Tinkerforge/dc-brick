/* dc-brick
 * Copyright (C) 2011-2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * dc.c: Implementation of DC-Brick specific functions
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "dc.h"

#include "config.h"
#include "communication.h"

#include "bricklib/com/com.h"
#include "bricklib/com/com_common.h"
#include "bricklib/logging/logging.h"
#include "bricklib/bricklet/bricklet_init.h"
#include "bricklib/drivers/dacc/dacc.h"
#include "bricklib/drivers/tc/tc.h"
#include "bricklib/drivers/adc/adc.h"
#include "bricklib/drivers/pio/pio.h"
#include "bricklib/drivers/usart/usart.h"
#include "bricklib/drivers/pwmc/pwmc.h"
#include "bricklib/drivers/usb/USBD_HAL.h"
#include "bricklib/utility/util_definitions.h"
#include "bricklib/utility/led.h"
#include "bricklib/utility/init.h"

#ifdef ENCODER
#include "bricklib/utility/pid.h"
#endif

#include <stdio.h>

Pin pin_input1 = PIN_INPUT1;
Pin pin_input2 = PIN_INPUT2;
Pin pin_slew_rate = PIN_SLEW_RATE;
Pin pin_feedback = PIN_FEEDBACK;
Pin pin_enable = PIN_ENABLE;
Pin pin_input_inv = PIN_INPUT_INV;
Pin pin_status_flag = PIN_STATUS_FLAG;
Pin pin_disable1 = PIN_DISABLE1;
Pin pin_disable2 = PIN_DISABLE2;
Pin pin_voltage_switch = VOLTAGE_STACK_SWITCH_PIN;

int32_t dc_velocity_goal = 0;
int32_t dc_velocity = 0;
uint16_t dc_acceleration = DC_ACCELERATION_DEFAULT;
uint16_t dc_pwm_frequency = DC_STARTUP_PWM_FREQUENCY;
uint16_t dc_minimum_voltage = DC_MINIMUM_VOLTAGE;
uint8_t dc_emergency_shutdown_counter = 0;
bool dc_enabled = false;
uint32_t dc_tick_counter = 0;
uint32_t dc_message_tick_counter = 0;
uint16_t dc_pwm_scale_value = 0;
uint16_t dc_current_velocity_period = 0;
uint8_t dc_mode = DC_MODE_DRIVE_BRAKE;
bool dc_velocity_reached = false;
bool dc_current_velocity = false;

int32_t dc_last_callback_velocity = 0;

uint8_t dc_led_error_reason = 0;

uint8_t dc_tick_calc_counter = 0;
uint32_t dc_current_sum = 0;
uint16_t dc_current = 0;

extern ComInfo com_info;
extern bool usb_first_connection;

#ifdef ENCODER
int8_t encoder_table[4][4]={{ 0,  1, -1,  0},
                            {-1,  0,  0,  1},
                            { 1,  0,  0, -1},
                            { 0, -1,  1,  0}};
int32_t encoder_count = 0;
int32_t encoder_count_last = 0;
uint8_t encoder_value_last = 0;

bool encoder_enabled = false;
int32_t encoder_count_external = 0;
uint16_t encoder_counts_per_revolution = 400;

Pin pin_encoder_a = BRICKLET_A_PIN_1_AD;
Pin pin_encoder_b = BRICKLET_A_PIN_2_DA;

PID pid;
int32_t pid_velocity;


void TC0_IrqHandler(void) {
	// acknowledge interrupt
	tc_channel_interrupt_ack(&ENCODER_TC_CHANNEL);

	if(led_is_on(LED_STD_RED)) {
		led_off(LED_STD_RED);
	} else {
		led_on(LED_STD_RED);
	}

	uint8_t encoder_value = PIO_Get(&pin_encoder_a);
	encoder_value |= (PIO_Get(&pin_encoder_b) << 1);

	int8_t add = encoder_table[encoder_value_last][encoder_value];
	encoder_count += add;
	encoder_count_external += add;
	encoder_value_last = encoder_value;
}

void encoder_init(void) {
	PIO_Configure(&pin_encoder_a, 1);
	PIO_Configure(&pin_encoder_b, 1);

    // Enable peripheral clock for TC
    PMC->PMC_PCER0 = 1 << ID_TC0;

    // Configure and enable TC interrupts
	NVIC_DisableIRQ(TC0_IRQn);
	NVIC_ClearPendingIRQ(TC0_IRQn);
	NVIC_SetPriority(TC0_IRQn, PRIORITY_ENCODER_TC0);
	NVIC_EnableIRQ(TC0_IRQn);

	tc_channel_init(&ENCODER_TC_CHANNEL,
	                TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_CPCTRG);

    // Interrupt in compare
    tc_channel_interrupt_set(&ENCODER_TC_CHANNEL, TC_IER_CPCS);

    ENCODER_COUNTER = 25;
}

bool encoder_tick(void) {
	static uint32_t encoder_tick_count = 0;

	encoder_tick_count++;
	if((encoder_tick_count % pid.sample_time) == 0) {
		encoder_count_last = encoder_count;
		encoder_count = 0;
		//printf("rpm: %d\n\r", encoder_count_last);

		return true;
	}
	return false;
}
#endif

void tick_task(const uint8_t tick_type) {
	static int8_t message_counter = 0;

	if(tick_type == TICK_TASK_TYPE_MESSAGE) {
		if(usb_first_connection && !usbd_hal_is_disabled(IN_EP)) {
			message_counter++;
			if(message_counter >= 100) {
				message_counter = 0;
				if(brick_init_enumeration(COM_USB)) {
					com_info.current = COM_USB;
					usb_first_connection = false;
					message_counter = 0;
				}
			}
		}
	}

	if(tick_type == TICK_TASK_TYPE_CALCULATION) {
		dc_tick_calc_counter++;
		dc_current_sum += adc_channel_get_data(CURRENT_CONSUMPTION_CHANNEL);
		if(dc_tick_calc_counter >= 100) {
			dc_current = dc_current_sum/100;
			dc_current_sum = 0;
			dc_tick_calc_counter = 0;
		}

		dc_tick_counter++;

		// Switch Output Voltage between extern and stack
		if(dc_get_external_voltage() < DC_VOLTAGE_EPSILON) {
			PIO_Set(&pin_voltage_switch);
		} else {
			PIO_Clear(&pin_voltage_switch);
		}

		if(!dc_enabled) {
			return;
		}

		// Emit current velocity callback if necessary
		if((dc_current_velocity_period != 0) &&
		   ((dc_tick_counter % dc_current_velocity_period) == 0)) {
			dc_current_velocity = true;
		}

		//if(!encoder_enabled) {
			if(dc_velocity_goal == dc_velocity) {
				return;
			}
		//}

		if(dc_acceleration == 0) {
			dc_velocity = dc_velocity_goal;
		} else {
			if(dc_velocity < dc_velocity_goal) {
				dc_velocity = MIN(dc_velocity + dc_acceleration,
				                  dc_velocity_goal);
			} else {
				dc_velocity = MAX(dc_velocity - dc_acceleration,
				                  dc_velocity_goal);
			}
		}


#ifdef ENCODER
		if(encoder_enabled) {
			if(encoder_tick()) {
				float setpoint = (dc_velocity/DC_VELOCITY_MULTIPLIER)*encoder_counts_per_revolution*pid.sample_time/(1000*60);
				float out;
				if(pid_compute(&pid, setpoint, (float)ABS(encoder_count_last), &out)) {
					pid_velocity = (int32_t)out;
		//			pid_print(&pid);
				}
			}
		}
#endif

		// Set new velocity
		dc_velocity_to_pwm();

		// Emit velocity reachead callback
		if(dc_velocity_goal == dc_velocity /*&& !encoder_enabled*/) {
			dc_velocity_reached = true;
		}
	} else if(tick_type == TICK_TASK_TYPE_MESSAGE) {
		dc_message_tick_counter++;

		if(dc_velocity_reached) {
			dc_velocity_reached = false;
			dc_velocity_reached_callback();
		}

		if(dc_current_velocity) {
			dc_current_velocity = false;
			dc_current_velocity_callback();
		}

		dc_check_error_callbacks();
	}
}

void dc_update_pwm_frequency(void) {
	// Calculate best possible frequency
	uint8_t cmr_cpre;
	for(cmr_cpre = 0; cmr_cpre < DC_NUM_PWM_FREQUENCIES; cmr_cpre++) {
		uint32_t frequency = (BOARD_MCK/(1 << cmr_cpre));

		if(dc_pwm_frequency > frequency/0xFFFF) {
			dc_pwm_scale_value = frequency/dc_pwm_frequency;
			break;
		}
	}

	// Set PWM frequency according to PWM mode (drive/brake vs drive/coast)
	if(dc_mode == DC_MODE_DRIVE_BRAKE) {
		PWMC_DisableChannel(PWM, INPUT1_CHANNEL);
		PWMC_DisableChannel(PWM, INPUT2_CHANNEL);

		PWMC_ConfigureChannel(PWM, INPUT1_CHANNEL, cmr_cpre, 0, 0);
		PWMC_SetPeriod(PWM, INPUT1_CHANNEL, dc_pwm_scale_value);

		PWMC_ConfigureChannel(PWM, INPUT2_CHANNEL, cmr_cpre, 0, 0);
		PWMC_SetPeriod(PWM, INPUT2_CHANNEL, dc_pwm_scale_value);

		PWMC_EnableChannel(PWM, INPUT1_CHANNEL);
		PWMC_EnableChannel(PWM, INPUT2_CHANNEL);

		dc_velocity_to_pwm();
	} else {
		PWMC_DisableChannel(PWM, DISABLE1_CHANNEL);
		PWMC_ConfigureChannel(PWM, DISABLE1_CHANNEL, cmr_cpre, 0, 0);
		PWMC_SetPeriod(PWM, DISABLE1_CHANNEL, dc_pwm_scale_value);

		PWMC_EnableChannel(PWM, DISABLE1_CHANNEL);
		dc_velocity_to_pwm();
	}
}

void dc_enable(void) {
	PIO_Set(&pin_enable);
	dc_enabled = true;

	dc_led_error_reason &= ~DC_LED_ERROR_SHUTDOWN;
	led_off(LED_STD_RED);
}

void dc_disable(void) {
	PIO_Clear(&pin_enable);
	dc_enabled = false;
	// Set current velocity to 0 and keep old goal
	dc_velocity = 0;
	dc_velocity_to_pwm();

	dc_led_error_reason &= ~DC_LED_ERROR_SHUTDOWN;
	led_off(LED_STD_RED);
}

void dc_init(void) {
#ifdef ENCODER
	pid_init(&pid,
	         PID_K_P_DEFAULT,
	         PID_K_I_DEFAULT,
	         PID_K_D_DEFAULT,
	         PID_SAMPLE_TIME_DEFAULT,
	         PID_MAX_OUT_DEFAULT,
	         PID_MIN_OUT_DEFAULT);

	encoder_init();
#endif

	Pin dc_pins[] = {PINS_DC};
	PIO_Configure(dc_pins, PIO_LISTSIZE(dc_pins));

	// Configure and enable power measurements
	Pin dc_power_management_pins[] = {VOLTAGE_STACK_PIN,
	                                  VOLTAGE_EXTERN_PIN,
	                                  VOLTAGE_STACK_SWITCH_PIN,
	                                  CURRENT_CONSUMPTION_PIN};
	PIO_Configure(dc_power_management_pins,
	              PIO_LISTSIZE(dc_power_management_pins));

	// Initialize PWM
	PMC->PMC_PCER0 = 1 << ID_PWM;
	dc_update_pwm_frequency();

	adc_channel_enable(VOLTAGE_EXTERN_CHANNEL);
	adc_channel_enable(VOLTAGE_STACK_CHANNEL);
	adc_channel_enable(CURRENT_CONSUMPTION_CHANNEL);
}

void dc_current_velocity_callback(void) {
	// Only emit callback if velocity has changed since last callback
	if(dc_last_callback_velocity == dc_velocity /*&& !encoder_enabled*/) {
		return;
	}

	dc_last_callback_velocity = dc_velocity;

	CurrentVelocityCallback cvs;
	com_make_default_header(&cvs, com_info.uid, sizeof(CurrentVelocityCallback), FID_CURRENT_VELOCITY);
	cvs.velocity = dc_velocity/DC_VELOCITY_MULTIPLIER;

	send_blocking_with_timeout(&cvs,
	                           sizeof(CurrentVelocityCallback),
	                           com_info.current);
}

void dc_velocity_reached_callback(void) {
	VelocityReachedCallback vrs;
	com_make_default_header(&vrs, com_info.uid, sizeof(VelocityReachedCallback), FID_VELOCITY_REACHED);
	vrs.velocity = dc_velocity/DC_VELOCITY_MULTIPLIER;

	send_blocking_with_timeout(&vrs,
	                           sizeof(VelocityReachedCallback),
	                           com_info.current);
}

void dc_check_error_callbacks(void) {
	const uint16_t external_voltage = dc_get_external_voltage();
	const uint16_t stack_voltage    = dc_get_stack_voltage();

	// Under Voltage if external voltage is below minimum voltage (regardless
	// of stack voltage), or if external voltage is zero and stack voltage is
	// below minimum voltage
	if((dc_message_tick_counter % 1000 == 0 && dc_enabled) &&
	   ((external_voltage > DC_VOLTAGE_EPSILON &&
		 external_voltage < dc_minimum_voltage) ||
		(external_voltage < DC_VOLTAGE_EPSILON &&
		 stack_voltage > DC_VOLTAGE_EPSILON &&
		 stack_voltage < dc_minimum_voltage))) {

		UnderVoltageCallback uvs;
		com_make_default_header(&uvs, com_info.uid, sizeof(UnderVoltageCallback), FID_UNDER_VOLTAGE);
		uvs.voltage = external_voltage < DC_VOLTAGE_EPSILON ? stack_voltage : external_voltage;

		send_blocking_with_timeout(&uvs,
		                           sizeof(UnderVoltageCallback),
		                           com_info.current);

		led_on(LED_STD_RED);
	// If there is no under voltage, we are currently enabled and the
	// status flag is low: There is a short-circuit or over-temperature
	// -> Emergency Shutdown
	} else if(!PIO_Get(&pin_status_flag) &&
	          dc_enabled &&
	          dc_mode == DC_MODE_DRIVE_BRAKE) {
		dc_emergency_shutdown_counter++;
		// Wait for DC_MAX_EMERGENCY_SHUTDOWN ms until callback is emitted
		if(dc_emergency_shutdown_counter >= DC_MAX_EMERGENCY_SHUTDOWN) {
			EmergencyShutdownCallback ess;
			com_make_default_header(&ess, com_info.uid, sizeof(EmergencyShutdownCallback), FID_EMERGENCY_SHUTDOWN);

			send_blocking_with_timeout(&ess,
									   sizeof(EmergencyShutdownCallback),
									   com_info.current);

			dc_disable();
			dc_emergency_shutdown_counter = 0;

			dc_led_error_reason |= DC_LED_ERROR_SHUTDOWN;
			led_on(LED_STD_RED);
		}
	} else {
		dc_emergency_shutdown_counter = 0;
		if(!(dc_led_error_reason & DC_LED_ERROR_SHUTDOWN) &&
		   (dc_tick_counter % 1000 == 0)) {
			led_off(LED_STD_RED);
		}
	}
}

void dc_full_brake(void) {
	dc_velocity_goal = 0;
	dc_velocity = 0;
	// In coast mode, actively pull down input1 and 2, in brake mode this
	// is done automatically if velocity is set to 0.
	if(dc_mode == DC_MODE_DRIVE_COAST) {
		PWM->PWM_CH_NUM[DISABLE1_CHANNEL].PWM_CDTYUPD = 0;
		PIO_Clear(&pin_input1);
		PIO_Clear(&pin_input2);
	} else {
		dc_velocity_to_pwm();
	}
}

void dc_set_mode(const uint8_t mode) {
	if(mode == DC_MODE_DRIVE_BRAKE) {
		pin_input1.type = PIO_PERIPH_B;
		pin_input2.type = PIO_PERIPH_B;
		pin_disable1.type = PIO_OUTPUT_0;
		PIO_Configure(&pin_input1, 1);
		PIO_Configure(&pin_input2, 1);
		PIO_Configure(&pin_disable1, 1);
	} else {
		pin_input1.type = PIO_OUTPUT_1;
		pin_input2.type = PIO_OUTPUT_0;
		pin_disable1.type = PIO_PERIPH_C;

		PIO_Configure(&pin_input1, 1);
		PIO_Configure(&pin_input2, 1);
		PIO_Configure(&pin_disable1, 1);
	}
	dc_mode = mode;
	dc_update_pwm_frequency();
	dc_velocity_to_pwm();
}

void dc_velocity_to_pwm(void) {
#ifdef ENCODER
	int32_t vel;

	if(encoder_enabled) {
		vel = pid_velocity;
	} else {
		vel = dc_velocity/DC_VELOCITY_MULTIPLIER;
	}
#endif

	int32_t vel = dc_velocity/DC_VELOCITY_MULTIPLIER;

	// Calculate duty cycle according to pwm frequency
	uint16_t duty = SCALE(ABS(vel),
	                      0, DC_VELOCITY_MAX,
	                      0, dc_pwm_scale_value);

	if(dc_mode == DC_MODE_DRIVE_BRAKE) {
		if(dc_velocity > 0) {
			PWM->PWM_CH_NUM[INPUT1_CHANNEL].PWM_CDTYUPD = 0;
			PWM->PWM_CH_NUM[INPUT2_CHANNEL].PWM_CDTYUPD = duty;
		} else {
			PWM->PWM_CH_NUM[INPUT2_CHANNEL].PWM_CDTYUPD = 0;
			PWM->PWM_CH_NUM[INPUT1_CHANNEL].PWM_CDTYUPD = duty;
		}
	} else {
		if(dc_velocity > 0) {
			PIO_Set(&pin_input1);
			PIO_Clear(&pin_input2);
		} else {
			PIO_Clear(&pin_input1);
			PIO_Set(&pin_input2);
		}
		PWM->PWM_CH_NUM[DISABLE1_CHANNEL].PWM_CDTYUPD = duty;
	}
}

uint16_t dc_get_external_voltage(void) {
    return adc_channel_get_data(VOLTAGE_EXTERN_CHANNEL) *
           VOLTAGE_EXTERN_REFERENCE *
           VOLTAGE_EXTERN_MULTIPLIER /
           VOLTAGE_MAX_VALUE;
}

uint16_t dc_get_stack_voltage(void) {
    return adc_channel_get_data(VOLTAGE_STACK_CHANNEL) *
           VOLTAGE_STACK_REFERENCE *
           VOLTAGE_STACK_MULTIPLIER /
           VOLTAGE_MAX_VALUE;
}

uint16_t dc_get_current_consumption(void) {
	return dc_current *
	       CURRENT_CONSUMPTION_REFERENCE *
	       CURRENT_CONSUMPTION_MULTIPLIER /
	       VOLTAGE_MAX_VALUE;
}
