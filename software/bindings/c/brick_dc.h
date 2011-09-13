/*************************************************************
 * This file was automatically generated on 13.09.2011.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICK_DC_H
#define BRICK_DC_H

#include "ip_connection.h"

typedef Device DC;

#define DC_CALLBACK_UNDER_VOLTAGE 21
#define DC_CALLBACK_EMERGENCY_SHUTDOWN 22
#define DC_CALLBACK_VELOCITY_REACHED 23
#define DC_CALLBACK_CURRENT_VELOCITY 24

void dc_create(DC *dc, const char *uid);

int dc_set_velocity(DC *dc, int16_t velocity);
int dc_get_velocity(DC *dc, int16_t *ret_velocity);
int dc_get_current_velocity(DC *dc, int16_t *ret_velocity);
int dc_set_acceleration(DC *dc, uint16_t acceleration);
int dc_get_acceleration(DC *dc, uint16_t *ret_acceleration);
int dc_set_pwm_frequency(DC *dc, uint16_t frequency);
int dc_get_pwm_frequency(DC *dc, uint16_t *ret_frequency);
int dc_full_brake(DC *dc);
int dc_get_stack_input_voltage(DC *dc, uint16_t *ret_voltage);
int dc_get_external_input_voltage(DC *dc, uint16_t *ret_voltage);
int dc_get_current_consumption(DC *dc, uint16_t *ret_voltage);
int dc_enable(DC *dc);
int dc_disable(DC *dc);
int dc_is_enabled(DC *dc, bool *ret_enabled);
int dc_set_minimum_voltage(DC *dc, uint16_t voltage);
int dc_get_minimum_voltage(DC *dc, uint16_t *ret_voltage);
int dc_set_drive_mode(DC *dc, uint8_t mode);
int dc_get_drive_mode(DC *dc, uint8_t *ret_mode);
int dc_set_current_velocity_period(DC *dc, uint16_t period);
int dc_get_current_velocity_period(DC *dc, uint16_t *ret_period);
int dc_under_voltage(DC *dc, uint16_t *ret_voltage);
int dc_emergency_shutdown(DC *dc);
int dc_velocity_reached(DC *dc, int16_t *ret_velocity);
int dc_current_velocity(DC *dc, int16_t *ret_velocity);

void dc_register_callback(DC *dc, uint8_t cb, void *func);

#endif