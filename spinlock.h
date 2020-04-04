#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
typedef struct spinlock_t {
	int val;
}spinlock_t;
//spinlock_t *flag;
int testnset(spinlock_t *flag);
void spinlock(spinlock_t *l);
void spinunlock(spinlock_t *l);
void spininit(spinlock_t *l);
//int l = 0;
/*int testnset(int *flag) {
	int tmp = *flag;
	*flag = 1;
	return tmp;
}*/
void spininit(spinlock_t *l) {
	l -> val = 0;
}
void spinlock(spinlock_t *l){   
	while (__sync_lock_test_and_set(&(l->val),1)) 
		;
}

void spinunlock(spinlock_t *l) {
	l->val = 0; 
}

