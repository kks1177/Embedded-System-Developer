// ring.c

#include "ring.h"

//#define D_QUEUE_MAX		100

//typedef struct _ring_q_t
//{
//	char q[D_QUEUE_MAX]; /*q buffer*/
//	int nqsize; /*q 버퍼 크기*/
//	int ndatasize; /*저장된 데이터 크기*/
//	int in;
//	int out;
//} ring_q_t;

bool ring_q_init(ring_q_t *rq)
{
	if (rq == NULL) return false;

	memset(rq, 0, sizeof(ring_q_t));
	rq->nqsize = D_QUEUE_MAX;

	return true;
}

void ring_q_deinit(ring_q_t *rq)
{
}

void ring_q_reset(ring_q_t *rq)
{
	if (rq) {
		memset(rq->q, 0, D_QUEUE_MAX);

		rq->ndatasize = 0;
		rq->in = 0;
		rq->out = 0;
	}
}

int ring_q_size(ring_q_t *rq)
{
	int size = 0;
 
	if (rq) {
		size = rq->ndatasize;
	}
	
	return size;
}

int ring_q_push(ring_q_t *rq, char *data, int nsize)
{
 char *src = NULL;
 char *dst = NULL;
 int push_size1 = 0;
 int push_size2 = 0;

 if (!rq || !data) return 0;
 
 if (rq->ndatasize + nsize >= rq->nqsize)
 {
 // overflow
 return -1;
 }

 src = data;
 dst = &rq->q[rq->in];
 push_size1 = rq->nqsize - rq->in;

 if (push_size1 > nsize) push_size1 = nsize;

 push_size2 = nsize - push_size1;
 memcpy(dst, src, push_size1*sizeof(char));
 rq->ndatasize += push_size1;

 if (push_size2 > 0)
 {
 int src_offset = push_size1;
 dst = rq->q;
 memcpy(dst, src + src_offset, push_size2*sizeof(char));
 rq->ndatasize += push_size2;
 }

 rq->in = (rq->in + nsize) % rq->nqsize;

 return nsize;
}

int ring_q_peek(ring_q_t *rq, char *data, int nsize)
{
 int peek_size1 = 0;
 int peek_size2 = 0;

 if (!rq || !data || nsize <= 0) return 0;


 if (rq->ndatasize <= 0)
 {

 return 0;
 }

 if (rq->ndatasize < nsize)
 {
 nsize = rq->ndatasize;
 }

 peek_size1 = rq->nqsize - rq->out;
 if (peek_size1 > nsize)
 {
 peek_size1 = nsize;
 }

 peek_size2 = nsize - peek_size1;

 if (peek_size1 > 0)
 {
 memcpy(data, &rq->q[rq->out], peek_size1*sizeof(char));
 }

 if (peek_size2 > 0)
 {
 memcpy(data + peek_size1, rq->q, peek_size2*sizeof(char));
 }

 return peek_size1 + peek_size2;
}

int ring_q_flush(ring_q_t *rq, int nsize)
{
 int i = 0;
 if (!rq || nsize <= 0) return -1;

 if (nsize > rq->ndatasize)
 {
 nsize = rq->ndatasize;
 }

 while (i<nsize)
 {
 rq->out = (rq->out + 1) % rq->nqsize;
 rq->ndatasize--;
 i++;
 }

 return nsize;
}

#if 1

// 원형 큐 (링 큐)
// https://ryanclaire.blogspot.com/2020/05/ring-quque-buffer-c-example.html
void ring_q_test(void)
{
	ring_q_t rq;
	char *push_data = "abcd1234";
	char peek_data[32] = { 0, };
	int ret = 0;

	printf("\n\nQueue Test Start.....\n");
	ring_q_init(&rq);
	ret = ring_q_push(&rq, push_data, strlen(push_data));
	printf("1. pushed : sz = %d\n", ret);
	ret = ring_q_push(&rq, push_data, strlen(push_data));
	printf("2. pushed : sz = %d\n", ret);
	
	ret = ring_q_size(&rq);
	printf("queue : sz = %d\n", ret);

	ret = ring_q_peek(&rq, peek_data, 50);
	printf("peek : sz = %d\n", ret);
	printf("%s\n", peek_data);
	
	ret = ring_q_flush(&rq, ret);
	printf("flush : sz = %d\n", ret);	
	
	ring_q_deinit(&rq);
}

#endif
