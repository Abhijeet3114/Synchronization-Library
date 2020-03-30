#include<stdio.h>
#include<stdlib.h>
#include<linux/sched.h>
#include "queue.h"
#include "list.h"

typedef struct semaphore {
	int val;
	int sl;
	//spinlock lk;
	list l;
}semaphore;
struct task_struct current; //global current task 
que *q;
void sem_init(semaphore *s, int initval) {
	s->val = initval;
	s->sl = 0;
	return;
}
void block(semaphore *s) {
	listappend(s->l, current); //Append Current Process to Wait Queue
	spinunlock(&(s->sl));
	schedule();
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
void signal(seamphore *s) {
	spinlock(*(s->sl));
	(s->val)++;
	x = deq(s->l) //Wait Queue
	enq(q, x); // Add dequed process to Ready Queue
	spinunlock(*(s->sl));
	return;
}