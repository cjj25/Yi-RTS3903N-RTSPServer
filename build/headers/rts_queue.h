/*
 * Realtek Semiconductor Corp.
 *
 * rts_queue.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTS_QUEUE_H
#define _RTS_QUEUE_H

typedef void *Item;

typedef struct rts_queue *Queue;

typedef void (*cleanup_item_func)(Item item);

Queue rts_queue_init();
void rts_queue_destroy(Queue q);
int rts_queue_empty(Queue q);

int rts_queue_push_back(Queue q, Item item);
Item rts_queue_pop(Queue q);
void rts_queue_clear(Queue q, cleanup_item_func cleanup);

void rts_queue_del(Queue q, Item item);
int rts_queue_insert(Queue q, Item newitem, Item item, int before);
int rts_queue_insert_at(Queue q, Item newitem, long index);
int rts_queue_swap(Queue q, Item a, Item b);
int rts_queue_check(Queue q, Item item);

int rts_queue_lock(Queue q);
int rts_queue_unlock(Queue q);

Item rts_queue_enumerate(Queue q, long index);
long rts_queue_count(Queue q);
int rts_queue_add(Queue q, Item item);
void rts_queue_rm(Queue q, Item item);

#define traverse_queue(q, func, arg...) \
	do {\
		int i;\
		for (i = 0; q && i < rts_queue_count(q); i++) {\
			Item item = rts_queue_enumerate(q, i);\
			func(item, ##arg);\
		}\
	} while (0)

#endif
