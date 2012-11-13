/* dc-brick
 * Copyright (C) 2010-2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: Implementation of DC-Brick specific messages
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


#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib/com/com_common.h"

#define FID_SET_VELOCITY 1
#define FID_GET_VELOCITY 2
#define FID_GET_CURRENT_VELOCITY 3
#define FID_SET_ACCELERATION 4
#define FID_GET_ACCELERATION 5
#define FID_SET_PWM_FREQUENCY 6
#define FID_GET_PWM_FREQUENCY 7
#define FID_FULL_BRAKE 8
#define FID_GET_STACK_INPUT_VOLTAGE 9
#define FID_GET_EXTERNAL_INPUT_VOLTAGE 10
#define FID_GET_CURRENT_CONSUMPTION 11
#define FID_ENABLE 12
#define FID_DISABLE 13
#define FID_IS_ENABLED 14
#define FID_SET_MINIMUM_VOLTAGE 15
#define FID_GET_MINIMUM_VOLTAGE 16
#define FID_SET_DRIVE_MODE 17
#define FID_GET_DRIVE_MODE 18
#define FID_SET_CURRENT_VELOCITY_PERIOD 19
#define FID_GET_CURRENT_VELOCITY_PERIOD 20
#define FID_UNDER_VOLTAGE 21
#define FID_EMERGENCY_SHUTDOWN 22
#define FID_VELOCITY_REACHED 23
#define FID_CURRENT_VELOCITY 24

#define COM_MESSAGES_USER \
	{FID_SET_VELOCITY, (message_handler_func_t)set_velocity}, \
	{FID_GET_VELOCITY, (message_handler_func_t)get_velocity}, \
	{FID_GET_CURRENT_VELOCITY, (message_handler_func_t)get_current_velocity}, \
	{FID_SET_ACCELERATION, (message_handler_func_t)set_acceleration}, \
	{FID_GET_ACCELERATION, (message_handler_func_t)get_acceleration}, \
	{FID_SET_PWM_FREQUENCY, (message_handler_func_t)set_pwm_frequency}, \
	{FID_GET_PWM_FREQUENCY, (message_handler_func_t)get_pwm_frequency}, \
	{FID_FULL_BRAKE, (message_handler_func_t)full_brake}, \
	{FID_GET_STACK_INPUT_VOLTAGE, (message_handler_func_t)get_stack_input_voltage}, \
	{FID_GET_EXTERNAL_INPUT_VOLTAGE, (message_handler_func_t)get_external_input_voltage}, \
	{FID_GET_CURRENT_CONSUMPTION, (message_handler_func_t)get_current_consumption}, \
	{FID_ENABLE, (message_handler_func_t)enable}, \
	{FID_DISABLE, (message_handler_func_t)disable}, \
	{FID_IS_ENABLED, (message_handler_func_t)is_enabled}, \
	{FID_SET_MINIMUM_VOLTAGE, (message_handler_func_t)set_minimum_voltage}, \
	{FID_GET_MINIMUM_VOLTAGE, (message_handler_func_t)get_minimum_voltage}, \
	{FID_SET_DRIVE_MODE, (message_handler_func_t)set_drive_mode}, \
	{FID_GET_DRIVE_MODE, (message_handler_func_t)get_drive_mode}, \
	{FID_SET_CURRENT_VELOCITY_PERIOD, (message_handler_func_t)set_current_velocity_period}, \
	{FID_GET_CURRENT_VELOCITY_PERIOD, (message_handler_func_t)get_current_velocity_period},

typedef struct {
	MessageHeader header;
	int16_t velocity;
} __attribute__((__packed__)) SetVelocity;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetVelocity;

typedef struct {
	MessageHeader header;
	int16_t velocity;
} __attribute__((__packed__)) GetVelocityReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetCurrentVelocity;

typedef struct {
	MessageHeader header;
	int16_t velocity;
} __attribute__((__packed__)) GetCurrentVelocityReturn;

typedef struct {
	MessageHeader header;
	uint16_t acceleration;
} __attribute__((__packed__)) SetAcceleration;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetAcceleration;

typedef struct {
	MessageHeader header;
	uint16_t acceleration;
} __attribute__((__packed__)) GetAccelerationReturn;

typedef struct {
	MessageHeader header;
	uint16_t frequency;
} __attribute__((__packed__)) SetPWMFrequency;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetPWMFrequency;

typedef struct {
	MessageHeader header;
	uint16_t frequency;
} __attribute__((__packed__)) GetPWMFrequencyReturn;


typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) FullBrake;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetStackInputVoltage;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) GetStackInputVoltageReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetExternalInputVoltage;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) GetExternalInputVoltageReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetCurrentConsumption;

typedef struct {
	MessageHeader header;
	uint16_t current;
} __attribute__((__packed__)) GetCurrentConsumptionReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) Enable;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) Disable;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) IsEnabled;

typedef struct {
	MessageHeader header;
	bool enabled;
} __attribute__((__packed__)) IsEnabledReturn;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) SetMinimumVoltage;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetMinimumVoltage;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) GetMinimumVoltageReturn;

typedef struct {
	MessageHeader header;
	uint8_t mode;
} __attribute__((__packed__)) SetDriveMode;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetDriveMode;

typedef struct {
	MessageHeader header;
	uint16_t mode;
} __attribute__((__packed__)) GetDriveModeReturn;

typedef struct {
	MessageHeader header;
	uint16_t period;
} __attribute__((__packed__)) SetCurrentVelocityPeriod;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetCurrentVelocityPeriod;

typedef struct {
	MessageHeader header;
	uint16_t period;
} __attribute__((__packed__)) GetCurrentVelocityPeriodReturn;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) UnderVoltageSignal;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) EmergencyShutdownSignal;

typedef struct {
	MessageHeader header;
	int16_t velocity;
} __attribute__((__packed__)) VelocityReachedSignal;

typedef struct {
	MessageHeader header;
	int16_t velocity;
} __attribute__((__packed__)) CurrentVelocitySignal;

void set_velocity(const ComType com, const SetVelocity *data);
void get_velocity(const ComType com, const GetVelocity *data);
void get_current_velocity(const ComType com, const GetCurrentVelocity *data);
void set_acceleration(const ComType com, const SetAcceleration *data);
void get_acceleration(const ComType com, const GetAcceleration *data);
void set_pwm_frequency(const ComType com, const SetPWMFrequency *data);
void get_pwm_frequency(const ComType com, const GetPWMFrequency *data);
void full_brake(const ComType com, const FullBrake *data);
void get_stack_input_voltage(const ComType com, const GetStackInputVoltage *data);
void get_external_input_voltage(const ComType com, const GetExternalInputVoltage *data);
void get_current_consumption(const ComType com, const GetCurrentConsumption *data);
void enable(const ComType com, const Enable *data);
void disable(const ComType com, const Disable *data);
void is_enabled(const ComType com, const IsEnabled *data);
void set_minimum_voltage(const ComType com, const SetMinimumVoltage *data);
void get_minimum_voltage(const ComType com, const GetMinimumVoltage *data);
void set_drive_mode(const ComType com, const SetDriveMode *data);
void get_drive_mode(const ComType com, const GetDriveMode *data);
void set_current_velocity_period(const ComType com, const SetCurrentVelocityPeriod *data);
void get_current_velocity_period(const ComType com, const GetCurrentVelocityPeriod *data);

#endif
