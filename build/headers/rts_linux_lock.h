/*
 * Realtek Semiconductor Corp.
 *
 * librtscamkit/rts_linux_lock.h
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTS_LINUX_LOCK_H
#define _RTS_LINUX_LOCK_H

#include <sys/ipc.h>

int rts_semaphore_allocation(key_t key, int nsem, int sem_flags);
int rts_semaphore_deallocate(int semid);
int rts_semaphore_wait(int semid, int sem_num);
int rts_semaphore_post(int semid, int sem_num);
int rts_semaphore_initialize(int semid, int sem_num);
int binary_semaphore_getval(int semid, int semnum);

#endif
