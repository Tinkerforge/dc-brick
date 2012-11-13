/* dc-brick
 * Copyright (C) 2011-2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * dc.h: Implementation of DC-Brick specific functions
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

#ifndef DC_H
#define DC_H

#include <stdint.h>

#define DC_VELOCITY_MULTIPLIER  1000
#define DC_VELOCITY_MAX         0x7fff
#define DC_ACCELERATION_MAX     0xFFFF
#define DC_ACCELERATION_DEFAULT 10000

#define DC_VOLTAGE_EPSILON      1000

#define DC_MAX_PWM_FREQUENCY 20000
#define DC_MIN_PWM_FREQUENCY 1
#define DC_STARTUP_PWM_FREQUENCY 15000

#define DC_PWM_MAX_DUTY_CYCLE 5000

#define DC_TC_CHANNEL_NUM 0
#define DC_TC_CHANNEL (TC0->TC_CHANNEL[DC_TC_CHANNEL_NUM])
#define DC_COUNTER DC_TC_CHANNEL.TC_RC
#define DC_MINIMUM_VOLTAGE 6000
#define DC_MAXIMUM_VOLTAGE 28000
#define DC_MAX_EMERGENCY_SHUTDOWN 50

#define DC_MODE_DRIVE_BRAKE 0
#define DC_MODE_DRIVE_COAST 1

#define DC_NUM_PWM_FREQUENCIES 11  // BOARD_MCK/2^0 .. 2^10

#define DC_LED_ERROR_SHUTDOWN 1

void new_connection(void);
void tick_task(const uint8_t tick_type);

void dc_enable(void);
void dc_disable(void);
void dc_init(void);
void dc_velocity_to_pwm(void);
uint16_t dc_get_external_voltage(void);
uint16_t dc_get_stack_voltage(void);
uint16_t dc_get_current_consumption(void);
void dc_check_error_signals(void);
void dc_update_pwm_frequency(void);
void dc_current_velocity_signal(void);
void dc_velocity_reached_signal(void);
void dc_set_mode(const uint8_t mode);
void dc_full_brake(void);

#endif
