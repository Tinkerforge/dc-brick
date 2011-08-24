/* dc-brick
 * Copyright (C) 2010-2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: Implementation of DC-Brick specific messages
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

#include "communication.h"

#include "dc.h"

#include "bricklib/logging/logging.h"
#include "bricklib/com/com_common.h"
#include "bricklib/drivers/pwmc/pwmc.h"
#include "bricklib/drivers/adc/adc.h"

#include "bricklib/utility/util_definitions.h"

#include <stdint.h>
#include <stdio.h>

extern int32_t dc_velocity_goal;
extern int32_t dc_velocity;
extern uint16_t dc_acceleration;
extern uint16_t dc_minimum_voltage;
extern bool dc_enabled;
extern uint16_t dc_pwm_frequency;
extern uint16_t dc_current_velocity_period;
extern uint8_t dc_mode;

void set_velocity(uint8_t com, const SetVelocity *data) {
	dc_velocity_goal = data->velocity * DC_VELOCITY_MULTIPLIER;
}

void get_velocity(uint8_t com, const GetVelocity *data) {
	GetVelocityReturn gvr;

	gvr.stack_address = data->stack_address;
	gvr.type          = data->type;
	gvr.length        = sizeof(GetVelocityReturn);
	gvr.velocity      = dc_velocity_goal / DC_VELOCITY_MULTIPLIER;

	send_blocking_with_timeout(&gvr, sizeof(GetVelocityReturn), com);
}

void get_current_velocity(uint8_t com, const GetCurrentVelocity *data) {
	GetCurrentVelocityReturn gcvr;

	gcvr.stack_address = data->stack_address;
	gcvr.type          = data->type;
	gcvr.length        = sizeof(GetCurrentVelocityReturn);
	gcvr.velocity      = dc_velocity / DC_VELOCITY_MULTIPLIER;

	send_blocking_with_timeout(&gcvr, sizeof(GetCurrentVelocityReturn), com);
}

void set_acceleration(uint8_t com, const SetAcceleration *data) {
	dc_acceleration = data->acceleration;
}

void get_acceleration(uint8_t com, const GetAcceleration *data) {
	GetAccelerationReturn gar;

	gar.stack_address = data->stack_address;
	gar.type          = data->type;
	gar.length        = sizeof(GetAccelerationReturn);
	gar.acceleration  = dc_acceleration;

	send_blocking_with_timeout(&gar, sizeof(GetAccelerationReturn), com);
}

void set_pwm_frequency(uint8_t com, const SetPWMFrequency *data) {
	dc_pwm_frequency = BETWEEN(DC_MIN_PWM_FREQUENCY,
	                           data->frequency,
	                           DC_MAX_PWM_FREQUENCY);
	dc_update_pwm_frequency();
}

void get_pwm_frequency(uint8_t com, const GetPWMFrequency *data) {
	GetPWMFrequencyReturn gpwmfr;

	gpwmfr.stack_address = data->stack_address;
	gpwmfr.type          = data->type;
	gpwmfr.length        = sizeof(GetPWMFrequencyReturn);
	gpwmfr.frequency     = dc_pwm_frequency;

	send_blocking_with_timeout(&gpwmfr, sizeof(GetPWMFrequencyReturn), com);
}


void full_brake(uint8_t com, const FullBrake *data) {
	dc_full_brake();
}

void get_stack_input_voltage(uint8_t com, const GetStackInputVoltage *data) {
	GetStackInputVoltageReturn gsivr;

	gsivr.stack_address  = data->stack_address;
	gsivr.type           = data->type;
	gsivr.length         = sizeof(GetStackInputVoltageReturn);
    gsivr.voltage        = dc_get_stack_voltage();

	send_blocking_with_timeout(&gsivr, sizeof(GetStackInputVoltageReturn), com);
}

void get_external_input_voltage(uint8_t com, const GetExternalInputVoltage *data) {
	GetExternalInputVoltageReturn geivr;

	geivr.stack_address  = data->stack_address;
	geivr.type           = data->type;
	geivr.length         = sizeof(GetExternalInputVoltageReturn);
    geivr.voltage        = dc_get_external_voltage();

	send_blocking_with_timeout(&geivr, sizeof(GetExternalInputVoltageReturn), com);
}

void get_current_consumption(uint8_t com, const GetCurrentConsumption *data) {
	GetCurrentConsumptionReturn gccr;

	gccr.stack_address   = data->stack_address;
	gccr.type            = data->type;
	gccr.length          = sizeof(GetCurrentConsumptionReturn);
    gccr.current         = dc_get_current_consumption();

	send_blocking_with_timeout(&gccr, sizeof(GetCurrentConsumptionReturn), com);
}

void enable(uint8_t com, const Enable *data) {
	dc_enable();
}

void disable(uint8_t com, const Disable *data) {
	dc_disable();
}

void is_enabled(uint8_t com, const IsEnabled *data) {
	IsEnabledReturn ier;

	ier.stack_address = data->stack_address;
	ier.type          = data->type;
	ier.length        = sizeof(IsEnabledReturn);
	ier.enabled       = dc_enabled;

	send_blocking_with_timeout(&ier, sizeof(IsEnabledReturn), com);
}

void set_minimum_voltage(uint8_t com, const SetMinimumVoltage *data) {
	dc_minimum_voltage = BETWEEN(DC_MINIMUM_VOLTAGE,
	                             data->voltage,
	                             DC_MAXIMUM_VOLTAGE);
}

void get_minimum_voltage(uint8_t com, const GetMinimumVoltage *data) {
	GetMinimumVoltageReturn gmvr;

	gmvr.stack_address = data->stack_address;
	gmvr.type          = data->type;
	gmvr.length        = sizeof(GetMinimumVoltageReturn);
	gmvr.voltage       = dc_minimum_voltage;

	send_blocking_with_timeout(&gmvr, sizeof(GetMinimumVoltageReturn), com);
}

void set_drive_mode(uint8_t com, const SetDriveMode *data) {
	dc_set_mode(data->mode);
}

void get_drive_mode(uint8_t com, const GetDriveMode *data) {
	GetDriveModeReturn gdmr;

	gdmr.stack_address = data->stack_address;
	gdmr.type          = data->type;
	gdmr.length        = sizeof(GetDriveModeReturn);
	gdmr.mode          = dc_mode;

	send_blocking_with_timeout(&gdmr, sizeof(GetDriveModeReturn), com);
}

void set_current_velocity_period(uint8_t com, const SetCurrentVelocityPeriod *data) {
	dc_current_velocity_period = data->period;
}

void get_current_velocity_period(uint8_t com, const GetCurrentVelocityPeriod *data) {
	GetCurrentVelocityPeriodReturn gcvpr;

	gcvpr.stack_address = data->stack_address;
	gcvpr.type          = data->type;
	gcvpr.length        = sizeof(GetCurrentVelocityPeriodReturn);
	gcvpr.period        = dc_current_velocity_period;

	send_blocking_with_timeout(&gcvpr, sizeof(GetCurrentVelocityPeriodReturn), com);
}
