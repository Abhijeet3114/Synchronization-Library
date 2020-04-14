#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<pthread.h>
#include<unistd.h>
#include <sys/types.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <errno.h>
//#include "mutex_lock.h"
#include "cond.h"


typedef struct rwlock {
	int nActive; 
	int nPendingReads;
	int nPendingWrites;
	mutex m;
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
	mutex_lock (&r->m);
	r->nPendingReads++;
	if (r->nPendingWrites > 0) {
		cond_wait(&r->canRead, &(r->m)); 
	}
	while(r->nActive < 0) 
		cond_wait (&r->canRead, &r->m);
	r->nActive++;
	r->nPendingReads--;
	mutex_unlock (&r->m);
}
void unlockShared (rwlock *r) {
	mutex_lock(&r->m);
	r->nActive--;
	if(r->nActive == 0) {
		mutex_unlock(&r->m);
		cond_signal(&r->canWrite);
	} 
	else {
		mutex_unlock(&r->m);
	}
}
void lockExclusive (rwlock *r) {
	mutex_lock(&r->m);
	r->nPendingWrites++;
	while (r->nActive)
		cond_wait(&r->canWrite, &r->m);
	r->nPendingWrites--;
	
	r->nActive = -1;
	mutex_unlock(&r->m);
}
void unlockExclusive (rwlock *r) {
	int wakeReads;
	mutex_lock(&r->m);
	r->nActive = 0;
	wakeReads = (r->nPendingReads != 0);
	mutex_unlock(&r->m);
	if(wakeReads)
		cond_broadcast(&r->canRead); 
	else
		cond_signal(&r->canWrite); 
}
void downgrade (rwlock *r) {
	int wakeReads;
	mutex_lock (&r->m);
	r->nActive = 1;
	wakeReads = (r->nPendingReads != 0);
	mutex_unlock (&r->m);
	if (wakeReads)
		cond_broadcast (&r->canRead); 
}
void upgrade (rwlock *r) {
	mutex_lock (&r->m);
	if (r->nActive == 1) {
		r->nActive = -1;
	} 
	else {
		r->nPendingWrites++;
		r->nActive--;
		while (r->nActive)
			cond_wait (&r->canWrite, &r->m);
		r->nPendingWrites--;
		r->nActive = -1;
	}
	mutex_unlock (&r->m);

}
