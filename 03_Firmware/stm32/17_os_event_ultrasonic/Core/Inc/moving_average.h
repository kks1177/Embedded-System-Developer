#ifndef __MOVING_AVERAGE_H__
#define __MOVING_AVERAGE_H__
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SIZE 10

typedef struct{
	float value[MAX_SIZE];
	float mean;
	uint8_t state;
}MOV_AVG_T;

float moving_avg(MOV_AVG_T*, float);

#ifdef __cplusplus
}
#endif

#endif // __MOVING_AVERAGE_H__
