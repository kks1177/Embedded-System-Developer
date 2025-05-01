#ifndef __APP_H__
#define __APP_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "main.h"
#include "moving_average.h"
#include "lcd.h"
#include "cmsis_os2.h"


#ifdef __cplusplus
extern "C" {
#endif

#define DELTA_T 30

typedef struct{
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

typedef struct link_s{
	MOV_AVG_T m;
	DIST_T d;
	MOV_AVG_T m_l;
	
	uint16_t cnt[2];
	GPIO_TypeDef* trigger_port;
	GPIO_TypeDef* echo_port;
	uint16_t trigger_pin;
	uint16_t echo_pin;
	
	struct link_s* pNext;
}SENSE_T;



void app_loop(void);

#ifdef __cplusplus
}
#endif

#endif // __APP_H__
