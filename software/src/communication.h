/* dc-brick
 * Copyright (C) 2010-2011 Olaf Lüke <olaf@tinkerforge.com>
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

#define TYPE_SET_VELOCITY 1
#define TYPE_GET_VELOCITY 2
#define TYPE_GET_CURRENT_VELOCITY 3
#define TYPE_SET_ACCELERATION 4
#define TYPE_GET_ACCELERATION 5
#define TYPE_SET_PWM_FREQUENCY 6
#define TYPE_GET_PWM_FREQUENCY 7
#define TYPE_FULL_BRAKE 8
#define TYPE_GET_STACK_INPUT_VOLTAGE 9
#define TYPE_GET_EXTERNAL_INPUT_VOLTAGE 10
#define TYPE_GET_CURRENT_CONSUMPTION 11
#define TYPE_ENABLE 12
#define TYPE_DISABLE 13
#define TYPE_IS_ENABLED 14
#define TYPE_SET_MINIMUM_VOLTAGE 15
#define TYPE_GET_MINIMUM_VOLTAGE 16
#define TYPE_SET_DRIVE_MODE 17
#define TYPE_GET_DRIVE_MODE 18
#define TYPE_SET_CURRENT_VELOCITY_PERIOD 19
#define TYPE_GET_CURRENT_VELOCITY_PERIOD 20
#define TYPE_UNDER_VOLTAGE 21
#define TYPE_EMERGENCY_SHUTDOWN 22
#define TYPE_VELOCITY_REACHED 23
#define TYPE_CURRENT_VELOCITY 24

#define COM_MESSAGES_USER \
	{TYPE_SET_VELOCITY, (message_handler_func_t)set_velocity}, \
	{TYPE_GET_VELOCITY, (message_handler_func_t)get_velocity}, \
	{TYPE_GET_CURRENT_VELOCITY, (message_handler_func_t)get_current_velocity}, \
	{TYPE_SET_ACCELERATION, (message_handler_func_t)set_acceleration}, \
	{TYPE_GET_ACCELERATION, (message_handler_func_t)get_acceleration}, \
	{TYPE_SET_PWM_FREQUENCY, (message_handler_func_t)set_pwm_frequency}, \
	{TYPE_GET_PWM_FREQUENCY, (message_handler_func_t)get_pwm_frequency}, \
	{TYPE_FULL_BRAKE, (message_handler_func_t)full_brake}, \
	{TYPE_GET_STACK_INPUT_VOLTAGE, (message_handler_func_t)get_stack_input_voltage}, \
	{TYPE_GET_EXTERNAL_INPUT_VOLTAGE, (message_handler_func_t)get_external_input_voltage}, \
	{TYPE_GET_CURRENT_CONSUMPTION, (message_handler_func_t)get_current_consumption}, \
	{TYPE_ENABLE, (message_handler_func_t)enable}, \
	{TYPE_DISABLE, (message_handler_func_t)disable}, \
	{TYPE_IS_ENABLED, (message_handler_func_t)is_enabled}, \
	{TYPE_SET_MINIMUM_VOLTAGE, (message_handler_func_t)set_minimum_voltage}, \
	{TYPE_GET_MINIMUM_VOLTAGE, (message_handler_func_t)get_minimum_voltage}, \
	{TYPE_SET_DRIVE_MODE, (message_handler_func_t)set_drive_mode}, \
	{TYPE_GET_DRIVE_MODE, (message_handler_func_t)get_drive_mode}, \
	{TYPE_SET_CURRENT_VELOCITY_PERIOD, (message_handler_func_t)set_current_velocity_period}, \
	{TYPE_GET_CURRENT_VELOCITY_PERIOD, (message_handler_func_t)get_current_velocity_period},

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int16_t velocity;
} __attribute__((__packed__)) SetVelocity;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetVelocity;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int16_t velocity;
} __attribute__((__packed__)) GetVelocityReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetCurrentVelocity;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int16_t velocity;
} __attribute__((__packed__)) GetCurrentVelocityReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t acceleration;
} __attribute__((__packed__)) SetAcceleration;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetAcceleration;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t acceleration;
} __attribute__((__packed__)) GetAccelerationReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t frequency;
} __attribute__((__packed__)) SetPWMFrequency;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetPWMFrequency;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t frequency;
} __attribute__((__packed__)) GetPWMFrequencyReturn;


typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) FullBrake;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetStackInputVoltage;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) GetStackInputVoltageReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetExternalInputVoltage;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) GetExternalInputVoltageReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetCurrentConsumption;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} __attribute__((__packed__)) GetCurrentConsumptionReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) Enable;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) Disable;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) IsEnabled;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	bool enabled;
} __attribute__((__packed__)) IsEnabledReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) SetMinimumVoltage;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetMinimumVoltage;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) GetMinimumVoltageReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint8_t mode;
} __attribute__((__packed__)) SetDriveMode;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint8_t length;
} __attribute__((__packed__)) GetDriveMode;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t mode;
} __attribute__((__packed__)) GetDriveModeReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t period;
} __attribute__((__packed__)) SetCurrentVelocityPeriod;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetCurrentVelocityPeriod;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t period;
} __attribute__((__packed__)) GetCurrentVelocityPeriodReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) UnderVoltageSignal;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) EmergencyShutdownSignal;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int16_t velocity;
} __attribute__((__packed__)) VelocityReachedSignal;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int16_t velocity;
} __attribute__((__packed__)) CurrentVelocitySignal;

void set_velocity(uint8_t com, const SetVelocity *data);
void get_velocity(uint8_t com, const GetVelocity *data);
void get_current_velocity(uint8_t com, const GetCurrentVelocity *data);
void set_acceleration(uint8_t com, const SetAcceleration *data);
void get_acceleration(uint8_t com, const GetAcceleration *data);
void set_pwm_frequency(uint8_t com, const SetPWMFrequency *data);
void get_pwm_frequency(uint8_t com, const GetPWMFrequency *data);
void full_brake(uint8_t com, const FullBrake *data);
void get_stack_input_voltage(uint8_t com, const GetStackInputVoltage *data);
void get_external_input_voltage(uint8_t com, const GetExternalInputVoltage *data);
void get_current_consumption(uint8_t com, const GetCurrentConsumption *data);
void enable(uint8_t com, const Enable *data);
void disable(uint8_t com, const Disable *data);
void is_enabled(uint8_t com, const IsEnabled *data);
void set_minimum_voltage(uint8_t com, const SetMinimumVoltage *data);
void get_minimum_voltage(uint8_t com, const GetMinimumVoltage *data);
void set_drive_mode(uint8_t com, const SetDriveMode *data);
void get_drive_mode(uint8_t com, const GetDriveMode *data);
void set_current_velocity_period(uint8_t com, const SetCurrentVelocityPeriod *data);
void get_current_velocity_period(uint8_t com, const GetCurrentVelocityPeriod *data);

#endif
