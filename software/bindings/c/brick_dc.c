/*************************************************************
 * This file was automatically generated on 2011-09-13.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#include "brick_dc.h"

#include <string.h>

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

typedef void (*under_voltage_func_t)(uint16_t);
typedef void (*emergency_shutdown_func_t)();
typedef void (*velocity_reached_func_t)(int16_t);
typedef void (*current_velocity_func_t)(int16_t);

#ifdef _MSC_VER
	#pragma pack(push)
	#pragma pack(1)

	#define PACKED
#else
	#define PACKED __attribute__((packed))
#endif

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t velocity;
} PACKED SetVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t velocity;
} PACKED GetVelocityReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetCurrentVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t velocity;
} PACKED GetCurrentVelocityReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t acceleration;
} PACKED SetAcceleration;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetAcceleration;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t acceleration;
} PACKED GetAccelerationReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t frequency;
} PACKED SetPWMFrequency;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetPWMFrequency;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t frequency;
} PACKED GetPWMFrequencyReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED FullBrake;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetStackInputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetStackInputVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetExternalInputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetExternalInputVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetCurrentConsumption;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetCurrentConsumptionReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED Enable;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED Disable;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED IsEnabled;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	bool enabled;
} PACKED IsEnabledReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED SetMinimumVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetMinimumVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetMinimumVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t mode;
} PACKED SetDriveMode;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetDriveMode;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t mode;
} PACKED GetDriveModeReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t period;
} PACKED SetCurrentVelocityPeriod;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetCurrentVelocityPeriod;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t period;
} PACKED GetCurrentVelocityPeriodReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED UnderVoltageCallback;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED EmergencyShutdownCallback;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t velocity;
} PACKED VelocityReachedCallback;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int16_t velocity;
} PACKED CurrentVelocityCallback;

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

int dc_set_velocity(DC *dc, int16_t velocity) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	SetVelocity sv;
	sv.stack_id = dc->stack_id;
	sv.type = TYPE_SET_VELOCITY;
	sv.length = sizeof(SetVelocity);
	sv.velocity = velocity;

	ipcon_device_write(dc, (char *)&sv, sizeof(SetVelocity));

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_get_velocity(DC *dc, int16_t *ret_velocity) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_GET_VELOCITY;
	dc->answer.length = sizeof(GetVelocityReturn);
	GetVelocity gv;
	gv.stack_id = dc->stack_id;
	gv.type = TYPE_GET_VELOCITY;
	gv.length = sizeof(GetVelocity);

	ipcon_device_write(dc, (char *)&gv, sizeof(GetVelocity));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	GetVelocityReturn *gvr = (GetVelocityReturn *)dc->answer.buffer;
	*ret_velocity = gvr->velocity;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_get_current_velocity(DC *dc, int16_t *ret_velocity) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_GET_CURRENT_VELOCITY;
	dc->answer.length = sizeof(GetCurrentVelocityReturn);
	GetCurrentVelocity gcv;
	gcv.stack_id = dc->stack_id;
	gcv.type = TYPE_GET_CURRENT_VELOCITY;
	gcv.length = sizeof(GetCurrentVelocity);

	ipcon_device_write(dc, (char *)&gcv, sizeof(GetCurrentVelocity));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	GetCurrentVelocityReturn *gcvr = (GetCurrentVelocityReturn *)dc->answer.buffer;
	*ret_velocity = gcvr->velocity;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_set_acceleration(DC *dc, uint16_t acceleration) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	SetAcceleration sa;
	sa.stack_id = dc->stack_id;
	sa.type = TYPE_SET_ACCELERATION;
	sa.length = sizeof(SetAcceleration);
	sa.acceleration = acceleration;

	ipcon_device_write(dc, (char *)&sa, sizeof(SetAcceleration));

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_get_acceleration(DC *dc, uint16_t *ret_acceleration) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_GET_ACCELERATION;
	dc->answer.length = sizeof(GetAccelerationReturn);
	GetAcceleration ga;
	ga.stack_id = dc->stack_id;
	ga.type = TYPE_GET_ACCELERATION;
	ga.length = sizeof(GetAcceleration);

	ipcon_device_write(dc, (char *)&ga, sizeof(GetAcceleration));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	GetAccelerationReturn *gar = (GetAccelerationReturn *)dc->answer.buffer;
	*ret_acceleration = gar->acceleration;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_set_pwm_frequency(DC *dc, uint16_t frequency) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	SetPWMFrequency spf;
	spf.stack_id = dc->stack_id;
	spf.type = TYPE_SET_PWM_FREQUENCY;
	spf.length = sizeof(SetPWMFrequency);
	spf.frequency = frequency;

	ipcon_device_write(dc, (char *)&spf, sizeof(SetPWMFrequency));

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_get_pwm_frequency(DC *dc, uint16_t *ret_frequency) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_GET_PWM_FREQUENCY;
	dc->answer.length = sizeof(GetPWMFrequencyReturn);
	GetPWMFrequency gpf;
	gpf.stack_id = dc->stack_id;
	gpf.type = TYPE_GET_PWM_FREQUENCY;
	gpf.length = sizeof(GetPWMFrequency);

	ipcon_device_write(dc, (char *)&gpf, sizeof(GetPWMFrequency));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	GetPWMFrequencyReturn *gpfr = (GetPWMFrequencyReturn *)dc->answer.buffer;
	*ret_frequency = gpfr->frequency;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_full_brake(DC *dc) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	FullBrake fb;
	fb.stack_id = dc->stack_id;
	fb.type = TYPE_FULL_BRAKE;
	fb.length = sizeof(FullBrake);

	ipcon_device_write(dc, (char *)&fb, sizeof(FullBrake));

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_get_stack_input_voltage(DC *dc, uint16_t *ret_voltage) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_GET_STACK_INPUT_VOLTAGE;
	dc->answer.length = sizeof(GetStackInputVoltageReturn);
	GetStackInputVoltage gsiv;
	gsiv.stack_id = dc->stack_id;
	gsiv.type = TYPE_GET_STACK_INPUT_VOLTAGE;
	gsiv.length = sizeof(GetStackInputVoltage);

	ipcon_device_write(dc, (char *)&gsiv, sizeof(GetStackInputVoltage));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	GetStackInputVoltageReturn *gsivr = (GetStackInputVoltageReturn *)dc->answer.buffer;
	*ret_voltage = gsivr->voltage;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_get_external_input_voltage(DC *dc, uint16_t *ret_voltage) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_GET_EXTERNAL_INPUT_VOLTAGE;
	dc->answer.length = sizeof(GetExternalInputVoltageReturn);
	GetExternalInputVoltage geiv;
	geiv.stack_id = dc->stack_id;
	geiv.type = TYPE_GET_EXTERNAL_INPUT_VOLTAGE;
	geiv.length = sizeof(GetExternalInputVoltage);

	ipcon_device_write(dc, (char *)&geiv, sizeof(GetExternalInputVoltage));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	GetExternalInputVoltageReturn *geivr = (GetExternalInputVoltageReturn *)dc->answer.buffer;
	*ret_voltage = geivr->voltage;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_get_current_consumption(DC *dc, uint16_t *ret_voltage) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_GET_CURRENT_CONSUMPTION;
	dc->answer.length = sizeof(GetCurrentConsumptionReturn);
	GetCurrentConsumption gcc;
	gcc.stack_id = dc->stack_id;
	gcc.type = TYPE_GET_CURRENT_CONSUMPTION;
	gcc.length = sizeof(GetCurrentConsumption);

	ipcon_device_write(dc, (char *)&gcc, sizeof(GetCurrentConsumption));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	GetCurrentConsumptionReturn *gccr = (GetCurrentConsumptionReturn *)dc->answer.buffer;
	*ret_voltage = gccr->voltage;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_enable(DC *dc) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	Enable e;
	e.stack_id = dc->stack_id;
	e.type = TYPE_ENABLE;
	e.length = sizeof(Enable);

	ipcon_device_write(dc, (char *)&e, sizeof(Enable));

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_disable(DC *dc) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	Disable d;
	d.stack_id = dc->stack_id;
	d.type = TYPE_DISABLE;
	d.length = sizeof(Disable);

	ipcon_device_write(dc, (char *)&d, sizeof(Disable));

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_is_enabled(DC *dc, bool *ret_enabled) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_IS_ENABLED;
	dc->answer.length = sizeof(IsEnabledReturn);
	IsEnabled ie;
	ie.stack_id = dc->stack_id;
	ie.type = TYPE_IS_ENABLED;
	ie.length = sizeof(IsEnabled);

	ipcon_device_write(dc, (char *)&ie, sizeof(IsEnabled));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	IsEnabledReturn *ier = (IsEnabledReturn *)dc->answer.buffer;
	*ret_enabled = ier->enabled;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_set_minimum_voltage(DC *dc, uint16_t voltage) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	SetMinimumVoltage smv;
	smv.stack_id = dc->stack_id;
	smv.type = TYPE_SET_MINIMUM_VOLTAGE;
	smv.length = sizeof(SetMinimumVoltage);
	smv.voltage = voltage;

	ipcon_device_write(dc, (char *)&smv, sizeof(SetMinimumVoltage));

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_get_minimum_voltage(DC *dc, uint16_t *ret_voltage) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_GET_MINIMUM_VOLTAGE;
	dc->answer.length = sizeof(GetMinimumVoltageReturn);
	GetMinimumVoltage gmv;
	gmv.stack_id = dc->stack_id;
	gmv.type = TYPE_GET_MINIMUM_VOLTAGE;
	gmv.length = sizeof(GetMinimumVoltage);

	ipcon_device_write(dc, (char *)&gmv, sizeof(GetMinimumVoltage));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	GetMinimumVoltageReturn *gmvr = (GetMinimumVoltageReturn *)dc->answer.buffer;
	*ret_voltage = gmvr->voltage;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_set_drive_mode(DC *dc, uint8_t mode) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	SetDriveMode sdm;
	sdm.stack_id = dc->stack_id;
	sdm.type = TYPE_SET_DRIVE_MODE;
	sdm.length = sizeof(SetDriveMode);
	sdm.mode = mode;

	ipcon_device_write(dc, (char *)&sdm, sizeof(SetDriveMode));

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_get_drive_mode(DC *dc, uint8_t *ret_mode) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_GET_DRIVE_MODE;
	dc->answer.length = sizeof(GetDriveModeReturn);
	GetDriveMode gdm;
	gdm.stack_id = dc->stack_id;
	gdm.type = TYPE_GET_DRIVE_MODE;
	gdm.length = sizeof(GetDriveMode);

	ipcon_device_write(dc, (char *)&gdm, sizeof(GetDriveMode));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	GetDriveModeReturn *gdmr = (GetDriveModeReturn *)dc->answer.buffer;
	*ret_mode = gdmr->mode;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_set_current_velocity_period(DC *dc, uint16_t period) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	SetCurrentVelocityPeriod scvp;
	scvp.stack_id = dc->stack_id;
	scvp.type = TYPE_SET_CURRENT_VELOCITY_PERIOD;
	scvp.length = sizeof(SetCurrentVelocityPeriod);
	scvp.period = period;

	ipcon_device_write(dc, (char *)&scvp, sizeof(SetCurrentVelocityPeriod));

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_get_current_velocity_period(DC *dc, uint16_t *ret_period) {
	if(dc->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(dc);

	dc->answer.type = TYPE_GET_CURRENT_VELOCITY_PERIOD;
	dc->answer.length = sizeof(GetCurrentVelocityPeriodReturn);
	GetCurrentVelocityPeriod gcvp;
	gcvp.stack_id = dc->stack_id;
	gcvp.type = TYPE_GET_CURRENT_VELOCITY_PERIOD;
	gcvp.length = sizeof(GetCurrentVelocityPeriod);

	ipcon_device_write(dc, (char *)&gcvp, sizeof(GetCurrentVelocityPeriod));

	if(ipcon_answer_sem_wait_timeout(dc) != 0) {
		ipcon_sem_post_write(dc);
		return E_TIMEOUT;
	}

	GetCurrentVelocityPeriodReturn *gcvpr = (GetCurrentVelocityPeriodReturn *)dc->answer.buffer;
	*ret_period = gcvpr->period;

	ipcon_sem_post_write(dc);

	return E_OK;
}

int dc_callback_under_voltage(DC *dc, const unsigned char *buffer) {
	UnderVoltageCallback *uvc = (UnderVoltageCallback *)buffer;
	((under_voltage_func_t)dc->callbacks[uvc->type])(uvc->voltage);
	return sizeof(UnderVoltageCallback);
}

int dc_callback_emergency_shutdown(DC *dc, const unsigned char *buffer) {
	EmergencyShutdownCallback *esc = (EmergencyShutdownCallback *)buffer;
	((emergency_shutdown_func_t)dc->callbacks[esc->type])();
	return sizeof(EmergencyShutdownCallback);
}

int dc_callback_velocity_reached(DC *dc, const unsigned char *buffer) {
	VelocityReachedCallback *vrc = (VelocityReachedCallback *)buffer;
	((velocity_reached_func_t)dc->callbacks[vrc->type])(vrc->velocity);
	return sizeof(VelocityReachedCallback);
}

int dc_callback_current_velocity(DC *dc, const unsigned char *buffer) {
	CurrentVelocityCallback *cvc = (CurrentVelocityCallback *)buffer;
	((current_velocity_func_t)dc->callbacks[cvc->type])(cvc->velocity);
	return sizeof(CurrentVelocityCallback);
}

void dc_register_callback(DC *dc, uint8_t cb, void *func) {
    dc->callbacks[cb] = func;
}

void dc_create(DC *dc, const char *uid) {
	ipcon_device_create(dc, uid);

	dc->device_callbacks[TYPE_UNDER_VOLTAGE] = dc_callback_under_voltage;
	dc->device_callbacks[TYPE_EMERGENCY_SHUTDOWN] = dc_callback_emergency_shutdown;
	dc->device_callbacks[TYPE_VELOCITY_REACHED] = dc_callback_velocity_reached;
	dc->device_callbacks[TYPE_CURRENT_VELOCITY] = dc_callback_current_velocity;
}
