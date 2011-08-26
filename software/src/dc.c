/* dc-brick
 * Copyright (C) 2011 Olaf Lüke <olaf@tinkerforge.com>
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
#include "bricklib/drivers/adc/adc.h"
#include "bricklib/drivers/pio/pio.h"
#include "bricklib/drivers/usart/usart.h"
#include "bricklib/drivers/pwmc/pwmc.h"
#include "bricklib/utility/util_definitions.h"
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
uint16_t dc_pwm_scale_value = 0;
uint16_t dc_current_velocity_period = 0;
uint8_t dc_mode = DC_MODE_DRIVE_BRAKE;

int32_t dc_last_signal_velocity = 0;

extern ComType com_current;
extern uint8_t com_stack_id;

void tick_task(void) {
	if(!dc_enabled) {
		return;
	}
	dc_tick_counter++;

	// Switch Output Voltage between extern and stack
	if(adc_channel_get_data(VOLTAGE_EXTERN_CHANNEL) < MIN_EXTERN_VALUE) {
		PIO_Set(&pin_voltage_switch);
	} else {
		PIO_Clear(&pin_voltage_switch);
	}

	// Emit current velocity signal if necessary
	if((dc_current_velocity_period != 0) &&
	   ((dc_tick_counter % dc_current_velocity_period) == 0)) {
		dc_current_velocity_signal();
	}

	if(dc_velocity_goal == dc_velocity) {
		return;
	}

	if(dc_acceleration == 0) {
		dc_velocity = dc_velocity_goal;
	} else {
		if(dc_velocity < dc_velocity_goal) {
			dc_velocity = MIN(dc_velocity + dc_acceleration, dc_velocity_goal);
		} else {
			dc_velocity = MAX(dc_velocity - dc_acceleration, dc_velocity_goal);
		}
	}

	// Set new velocity
	dc_velocity_to_pwm();

	// Emit velocity reachead signal
	if(dc_velocity_goal == dc_velocity) {
		dc_velocity_reached_signal();
	}

	dc_check_error_signals();
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
}

void dc_disable(void) {
	PIO_Clear(&pin_enable);
	dc_enabled = false;
	// Set current velocity to 0 and keep old goal
	dc_velocity = 0;
}

void dc_init(void) {
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

void dc_current_velocity_signal(void) {
	// Only emit signal if velocity has changed since last signal
	if(dc_last_signal_velocity == dc_velocity) {
		return;
	}

	dc_last_signal_velocity = dc_velocity;

	CurrentVelocitySignal cvs = {
		com_stack_id,
		TYPE_CURRENT_VELOCITY,
		sizeof(CurrentVelocitySignal),
		dc_velocity/DC_VELOCITY_MULTIPLIER
	};

	send_blocking_with_timeout(&cvs,
	                           sizeof(CurrentVelocitySignal),
	                           com_current);
}

void dc_velocity_reached_signal(void) {
	VelocityReachedSignal vrs = {
		com_stack_id,
		TYPE_VELOCITY_REACHED,
		sizeof(VelocityReachedSignal),
		dc_velocity/DC_VELOCITY_MULTIPLIER
	};

	send_blocking_with_timeout(&vrs,
	                           sizeof(VelocityReachedSignal),
	                           com_current);
}

void dc_check_error_signals(void) {
	const uint16_t external_voltage = dc_get_external_voltage();
	const uint16_t stack_voltage    = dc_get_stack_voltage();

	// Under Voltage if external voltage is below minimum voltage (regardless
	// of stack voltage), or if external voltage is zero and stack velotage is
	// below minimum voltage
	if((dc_tick_counter % 1000 == 0 && dc_enabled) &&
	   ((external_voltage > DC_VOLTAGE_EPSILON &&
		 external_voltage < dc_minimum_voltage) ||
		(external_voltage < DC_VOLTAGE_EPSILON &&
		 stack_voltage > DC_VOLTAGE_EPSILON &&
		 stack_voltage < dc_minimum_voltage))) {
		UnderVoltageSignal uvs = {
				com_stack_id,
				TYPE_UNDER_VOLTAGE,
				sizeof(UnderVoltageSignal),
				external_voltage == 0 ? stack_voltage : external_voltage
		};

		send_blocking_with_timeout(&uvs,
		                           sizeof(UnderVoltageSignal),
		                           com_current);
	// If there is no under voltage, we are currently enabled and the
	// status flag is low: There is a short-circuit or over-temperature
	// -> Emergency Shutdown
	} else if(!PIO_Get(&pin_status_flag) &&
	          dc_enabled &&
	          dc_mode == DC_MODE_DRIVE_BRAKE) {
		dc_emergency_shutdown_counter++;
		// Wait for DC_MAX_EMERGENCY_SHUTDOWN ms until signal is emitted
		if(dc_emergency_shutdown_counter >= DC_MAX_EMERGENCY_SHUTDOWN) {
			EmergencyShutdownSignal ess = {
					com_stack_id,
					TYPE_EMERGENCY_SHUTDOWN,
					sizeof(EmergencyShutdownSignal),
			};

			send_blocking_with_timeout(&ess,
									   sizeof(EmergencyShutdownSignal),
									   com_current);

			dc_disable();
			dc_emergency_shutdown_counter = 0;
		}
	} else {
		dc_emergency_shutdown_counter = 0;
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

void dc_set_mode(uint8_t mode) {
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
	// Calculate duty cycle according to pwm frequency
	uint16_t duty = SCALE(ABS(dc_velocity/DC_VELOCITY_MULTIPLIER),
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
	return adc_channel_get_data(CURRENT_CONSUMPTION_CHANNEL) *
	       CURRENT_CONSUMPTION_REFERENCE *
	       CURRENT_CONSUMPTION_MULTIPLIER /
	       VOLTAGE_MAX_VALUE;
}
