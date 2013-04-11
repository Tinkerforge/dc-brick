/* dc-brick
 * Copyright (C) 2010-2012 Olaf Lüke <olaf@tinkerforge.com>
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

#ifdef ENCODER
#include "bricklib/utility/pid.h"
#include "bricklib/drivers/tc/tc.h"
#endif

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

#ifdef ENCODER
extern bool encoder_enabled;
extern int32_t encoder_count_external;
extern uint16_t encoder_counts_per_revolution;
extern PID pid;
#endif

void set_velocity(const ComType com, const SetVelocity *data) {
	dc_velocity_goal = data->velocity * DC_VELOCITY_MULTIPLIER;

	com_return_setter(com, data);
}

void get_velocity(const ComType com, const GetVelocity *data) {
	GetVelocityReturn gvr;

	gvr.header        = data->header;
	gvr.header.length = sizeof(GetVelocityReturn);
	gvr.velocity      = dc_velocity_goal / DC_VELOCITY_MULTIPLIER;

	send_blocking_with_timeout(&gvr, sizeof(GetVelocityReturn), com);
}

void get_current_velocity(const ComType com, const GetCurrentVelocity *data) {
	GetCurrentVelocityReturn gcvr;

	gcvr.header        = data->header;
	gcvr.header.length = sizeof(GetCurrentVelocityReturn);
	gcvr.velocity      = dc_velocity / DC_VELOCITY_MULTIPLIER;

	send_blocking_with_timeout(&gcvr, sizeof(GetCurrentVelocityReturn), com);
}

void set_acceleration(const ComType com, const SetAcceleration *data) {
	dc_acceleration = data->acceleration;

	com_return_setter(com, data);
}

void get_acceleration(const ComType com, const GetAcceleration *data) {
	GetAccelerationReturn gar;

	gar.header        = data->header;
	gar.header.length = sizeof(GetAccelerationReturn);
	gar.acceleration  = dc_acceleration;

	send_blocking_with_timeout(&gar, sizeof(GetAccelerationReturn), com);
}

void set_pwm_frequency(const ComType com, const SetPWMFrequency *data) {
	dc_pwm_frequency = BETWEEN(DC_MIN_PWM_FREQUENCY,
	                           data->frequency,
	                           DC_MAX_PWM_FREQUENCY);
	dc_update_pwm_frequency();

	com_return_setter(com, data);
}

void get_pwm_frequency(const ComType com, const GetPWMFrequency *data) {
	GetPWMFrequencyReturn gpwmfr;

	gpwmfr.header        = data->header;
	gpwmfr.header.length = sizeof(GetPWMFrequencyReturn);
	gpwmfr.frequency     = dc_pwm_frequency;

	send_blocking_with_timeout(&gpwmfr, sizeof(GetPWMFrequencyReturn), com);
}


void full_brake(const ComType com, const FullBrake *data) {
	dc_full_brake();

	com_return_setter(com, data);
}

void get_stack_input_voltage(const ComType com, const GetStackInputVoltage *data) {
	GetStackInputVoltageReturn gsivr;

	gsivr.header        = data->header;
	gsivr.header.length = sizeof(GetStackInputVoltageReturn);
    gsivr.voltage        = dc_get_stack_voltage();

	send_blocking_with_timeout(&gsivr, sizeof(GetStackInputVoltageReturn), com);
}

void get_external_input_voltage(const ComType com, const GetExternalInputVoltage *data) {
	GetExternalInputVoltageReturn geivr;

	geivr.header        = data->header;
	geivr.header.length = sizeof(GetExternalInputVoltageReturn);
    geivr.voltage        = dc_get_external_voltage();

	send_blocking_with_timeout(&geivr, sizeof(GetExternalInputVoltageReturn), com);
}

void get_current_consumption(const ComType com, const GetCurrentConsumption *data) {
	GetCurrentConsumptionReturn gccr;

	gccr.header          = data->header;
	gccr.header.length   = sizeof(GetCurrentConsumptionReturn);
    gccr.current         = dc_get_current_consumption();

	send_blocking_with_timeout(&gccr, sizeof(GetCurrentConsumptionReturn), com);
}

void enable(const ComType com, const Enable *data) {
	dc_enable();

	com_return_setter(com, data);
}

void disable(const ComType com, const Disable *data) {
	dc_disable();

	com_return_setter(com, data);
}

void is_enabled(const ComType com, const IsEnabled *data) {
	IsEnabledReturn ier;

	ier.header        = data->header;
	ier.header.length = sizeof(IsEnabledReturn);
	ier.enabled       = dc_enabled;

	send_blocking_with_timeout(&ier, sizeof(IsEnabledReturn), com);
}

void set_minimum_voltage(const ComType com, const SetMinimumVoltage *data) {
	dc_minimum_voltage = BETWEEN(DC_MINIMUM_VOLTAGE,
	                             data->voltage,
	                             DC_MAXIMUM_VOLTAGE);

	com_return_setter(com, data);
}

void get_minimum_voltage(const ComType com, const GetMinimumVoltage *data) {
	GetMinimumVoltageReturn gmvr;

	gmvr.header        = data->header;
	gmvr.header.length = sizeof(GetMinimumVoltageReturn);
	gmvr.voltage       = dc_minimum_voltage;

	send_blocking_with_timeout(&gmvr, sizeof(GetMinimumVoltageReturn), com);
}

void set_drive_mode(const ComType com, const SetDriveMode *data) {
	if (data->mode != DC_MODE_DRIVE_BRAKE && data->mode != DC_MODE_DRIVE_COAST) {
		com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	dc_set_mode(data->mode);

	com_return_setter(com, data);
}

void get_drive_mode(const ComType com, const GetDriveMode *data) {
	GetDriveModeReturn gdmr;

	gdmr.header        = data->header;
	gdmr.header.length = sizeof(GetDriveModeReturn);
	gdmr.mode          = dc_mode;

	send_blocking_with_timeout(&gdmr, sizeof(GetDriveModeReturn), com);
}

void set_current_velocity_period(const ComType com, const SetCurrentVelocityPeriod *data) {
	dc_current_velocity_period = data->period;

	com_return_setter(com, data);
}

void get_current_velocity_period(const ComType com, const GetCurrentVelocityPeriod *data) {
	GetCurrentVelocityPeriodReturn gcvpr;

	gcvpr.header        = data->header;
	gcvpr.header.length = sizeof(GetCurrentVelocityPeriodReturn);
	gcvpr.period        = dc_current_velocity_period;

	send_blocking_with_timeout(&gcvpr, sizeof(GetCurrentVelocityPeriodReturn), com);
}

#ifdef ENCODER

void enable_encoder(const ComType com, const EnableEncoder *data) {
	encoder_enabled = true;
	tc_channel_start(&ENCODER_TC_CHANNEL);
	com_return_setter(com, data);

	logdci("enable_encoder\n\r");
}

void disable_encoder(const ComType com, const DisableEncoder *data) {
	encoder_enabled = false;
	tc_channel_stop(&ENCODER_TC_CHANNEL);
	com_return_setter(com, data);

	logdci("disable_encoder\n\r");
}

void is_encoder_enabled(const ComType com, const IsEncoderEnabled *data) {
	IsEncoderEnabledReturn ieer;

	ieer.header        = data->header;
	ieer.header.length = sizeof(IsEncoderEnabledReturn);
	ieer.enabled       = encoder_enabled;

	send_blocking_with_timeout(&ieer, sizeof(IsEncoderEnabledReturn), com);

	logdci("is_encoder_enabled: %d\n\r", encoder_enabled);
}

void get_encoder_count(const ComType com, const GetEncoderCount *data) {
	GetEncoderCountReturn gecr;

	gecr.header        = data->header;
	gecr.header.length = sizeof(GetEncoderCountReturn);
	gecr.count         = encoder_count_external;

	if(data->reset) {
		encoder_count_external = 0;
	}

	send_blocking_with_timeout(&gecr, sizeof(GetEncoderCountReturn), com);

	logdci("get_encoder_count: %d\n\r", gecr.count);
}

void set_encoder_config(const ComType com, const SetEncoderConfig *data) {
	encoder_counts_per_revolution = data->counts_per_revolution;
	com_return_setter(com, data);

	logdci("set_encoder_config: %d\n\r", encoder_counts_per_revolution);
}

void get_encoder_config(const ComType com, const GetEncoderConfig *data) {
	GetEncoderConfigReturn gecr;

	gecr.header                = data->header;
	gecr.header.length         = sizeof(GetEncoderConfigReturn);
	gecr.counts_per_revolution = encoder_counts_per_revolution;

	send_blocking_with_timeout(&gecr, sizeof(GetEncoderConfigReturn), com);

	logdci("get_encoder_config: %d\n\r", encoder_counts_per_revolution);
}

void set_encoder_pid_config(const ComType com, const SetEncoderPIDConfig *data) {
	pid.sample_time = data->sample_time;
	pid_set_tuning(&pid, data->p, data->i, data->d);
	com_return_setter(com, data);

	logdci("set_encoder_pid_config: %d %d %d %d\n\r",
	       (int16_t)data->p,
	       (int16_t)data->i,
	       (int16_t)data->d,
	       data->sample_time);
}

void get_encoder_pid_config(const ComType com, const GetEncoderPIDConfig *data) {
	GetEncoderPIDConfigReturn gepidcr;

	gepidcr.header        = data->header;
	gepidcr.header.length = sizeof(GetEncoderPIDConfigReturn);
	gepidcr.p             = pid.k_p_orig;
	gepidcr.i             = pid.k_i_orig;
	gepidcr.d             = pid.k_d_orig;
	gepidcr.sample_time   = pid.sample_time;

	send_blocking_with_timeout(&gepidcr, sizeof(GetEncoderPIDConfigReturn), com);

	logdci("get_encoder_pid_config: %d %d %d %d\n\r",
	       (int16_t)gepidcr.p,
	       (int16_t)gepidcr.i,
	       (int16_t)gepidcr.d,
	       gepidcr.sample_time);
}
#endif
