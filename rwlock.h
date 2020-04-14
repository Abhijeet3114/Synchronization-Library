#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<pthread.h>
//#include "spinlock.h"
#include<unistd.h>
#include <sys/types.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <errno.h>
//#include "spinlock.h"
#include "cond.h"


typedef struct rwlock {
	int nActive; 
	int nPendingReads;
	int nPendingWrites;
	spinlock_t sl;
	semaphore sem;
	//mutex_t mut;
	condition canRead;
	condition canWrite;
}rwlock;
void rwinit(rwlock *r) {
	r -> nActive = 0;
	r -> nPendingReads = 0;
	r -> nPendingWrites = 0;
	cond_init(&(r -> canRead));
	cond_init(&(r -> canWrite));
	//mutex_init(&(r->mut));
}
void lockShared (rwlock *r) {
	spinlock (&r->sl);
	r->nPendingReads++;
	if (r->nPendingWrites > 0) {
		cond_wait_sl(&r->canRead, &(r->sl)); 
		//printf("reached here");
	}
	while(r->nActive < 0) 
		cond_wait_sl (&r->canRead, &r->sl);
	r->nActive++;
	r->nPendingReads--;
	spinunlock (&r->sl);
}
void unlockShared (rwlock *r) {
	spinlock(&r->sl);
	r->nActive--;
	if(r->nActive == 0) {
		spinunlock(&r->sl);
		cond_signal_sl(&r->canWrite);
	} 
	else {
		spinunlock(&r->sl);
	}
}
void lockExclusive (rwlock *r) {
	spinlock(&r->sl);
	r->nPendingWrites++;
	while (r->nActive)
		cond_wait_sl(&r->canWrite, &r->sl);
	r->nPendingWrites--;
	
	r->nActive = -1;
	spinunlock(&r->sl);
}
void unlockExclusive (rwlock *r) {
	int wakeReads;
	spinlock(&r->sl);
	r->nActive = 0;
	wakeReads = (r->nPendingReads != 0);
	spinunlock(&r->sl);
	if(wakeReads)
		cond_broadcast_sl(&r->canRead); 
	else
		cond_signal_sl(&r->canWrite); 
}
void downgrade (rwlock *r) {
	int wakeReads;
	spinlock (&r->sl);
	r->nActive = 1;
	wakeReads = (r->nPendingReads != 0);
	spinunlock (&r->sl);
	if (wakeReads)
		cond_broadcast_sl (&r->canRead); 
}
void upgrade (rwlock *r) {
	spinlock (&r->sl);
	if (r->nActive == 1) {
		r->nActive = -1;
	} 
	else {
		r->nPendingWrites++;
		r->nActive--;
		while (r->nActive)
			cond_wait_sl (&r->canWrite, &r->sl);
		r->nPendingWrites--;
		r->nActive = -1;
	}
	spinunlock (&r->sl);

}
