#include "moving_average.h"

float moving_avg(MOV_AVG_T* p, float val){
	float tmp_val;
	
	tmp_val = p->value[p->state];
	p->value[p->state] = val;
	p->state++;
	
	p->mean -= tmp_val / MAX_SIZE;
	p->mean += p->value[p->state-1] / MAX_SIZE;
	
	p->state %= MAX_SIZE;
	return p->mean;
}
