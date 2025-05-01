#ifndef __APP_H__
#define __APP_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "main.h"
#include "moving_average.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DELTA_T 30

//typedef struct{
//	float value[MAX_SIZE];
//	float mean;
//	uint8_t state;
//	bool flag;
//}MOV_AVG_T;

typedef struct{
	uint16_t cnt[2];
	uint16_t time_rising;
	uint32_t curr_t, prev_t;
	bool flag_tx;
	bool flag;
//	bool machine_flag;
//	bool mot_on_flag;
	float dist_mean;
	float velo_mean;
	float accl_mean;
}DIST_T;

typedef struct{
	MOV_AVG_T m;
	DIST_T d;
	
	GPIO_TypeDef* trigger_port;
	GPIO_TypeDef* echo_port;
	uint16_t trigger_pin;
	uint16_t echo_pin;
}SENSE_T;



void app_loop(void);

#ifdef __cplusplus
}
#endif

#endif // __APP_H__
