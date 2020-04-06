#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<pthread.h>
#include<unistd.h>
#include <sys/types.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <errno.h>
#include "spinlock.c"

typedef struct semaphore {
	int val;
	spinlock_t sl;
	int futex;
	//spinlock lk;
}semaphore;
void signal(semaphore *s);
void wait(semaphore *s);
void block(semaphore *s);
void sem_init(semaphore *s, int initialval);


void sem_init(semaphore *s, int initialval) {
	s->val = initialval;
	spininit(&(s->sl));
	return;
}
void block(semaphore *s) {
	spinunlock(&(s->sl));
    syscall(__NR_futex, &s->futex, FUTEX_WAIT, s->futex, NULL, 0, 0);
	return;
}
void wait(semaphore *s) {
	spinlock(&(s->sl)); // A
	while(s->val <=0) {
		block(s);  
		spinlock(&(s->sl)); // B
	}
	(s->val)--;
	spinunlock(&(s->sl));
	return;
}
void signal(semaphore *s) {
	pthread_t x;
	spinlock(&(s->sl));
	(s->val)++;
	//Wait Queue
	syscall(__NR_futex, &s->futex, FUTEX_WAKE, 1, NULL, 0, 0);
	//enq(q, x); // Add dequed process to Ready Queue
	spinunlock(&(s->sl));
	return;
}
