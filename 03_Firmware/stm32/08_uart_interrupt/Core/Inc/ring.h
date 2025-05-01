// ring.h

#ifndef __RING_H
#define __RING_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define D_QUEUE_MAX		100

typedef struct _ring_q_t
{
	char q[D_QUEUE_MAX]; /*q buffer*/
	int nqsize; /*q 버퍼 크기*/
	int ndatasize; /*저장된 데이터 크기*/
	int in;
	int out;
} ring_q_t;

bool ring_q_init(ring_q_t *rq);
void ring_q_deinit(ring_q_t *rq);
void ring_q_reset(ring_q_t *rq);
int ring_q_size(ring_q_t *rq);
int ring_q_push(ring_q_t *rq, char *data, int nsize);
int ring_q_peek(ring_q_t *rq, char *data, int nsize);
int ring_q_flush(ring_q_t *rq, int nsize);

void ring_q_test(void);

#ifdef __cplusplus
}
#endif

#endif // __RING_H
