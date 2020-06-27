

#include <sys/time.h>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "semaphore.h"
#include "mutex_test.h"

typedef struct condition
{
    mutex *m;
    int pointer; //pointer or address of the process or thread
    int count;
    //mutex_t mut;
    spinlock_t sl;
    semaphore sem;
}condition;

void cond_init(condition *c);
void cond_signal(condition *c);
void cond_broadcast(condition *c);
int cond_timed_wait(condition *c, mutex *m, const struct timespec * timeout);
int cond_wait(condition *c, mutex *m);


void cond_init(condition *c) {
    c->m = NULL; //initializing mutex
    c->pointer = 0;
    spininit(&c->sl);
    sem_init(&c->sem);
    c->count = 0;
}

 void cond_signal(condition *c) {
    __sync_fetch_and_add(&(c->pointer), 1); 
    syscall(SYS_futex, &(c->pointer), FUTEX_WAKE, 1, NULL, NULL, 0);
}

void cond_broadcast(condition *c) {
    mutex *m = c->m;
    if (!m) 
	   return;
        __sync_fetch_and_add(&(c->pointer), 1);
    syscall(SYS_futex, &(c->pointer), FUTEX_REQUEUE, 1, (void *) INT_MAX, m, 0);
}

int cond_timed_wait(condition *c, mutex *m, const struct timespec * timeout) {
    struct timespec deadlockTimeout = {10, 0};

    int state;
    int prev = c->pointer;
    if (c->m != m) {
        assert(c->m == NULL);
        mutex *old = __sync_val_compare_and_swap(&(c->m), 0, m);
        assert(old == NULL);
    }
    mutex_unlock(c->m);
    int einval = syscall(SYS_futex, &(c->pointer), FUTEX_WAIT, prev, timeout, NULL, 0);

    assert(einval == 0 || (einval == -1 && (errno == EAGAIN || errno == ETIMEDOUT)));
    if (einval == -1 && errno == ETIMEDOUT){
        einval = mutex_timed_lock(c->m, &deadlockTimeout);
        if (einval == ETIMEDOUT)
            return EDEADLOCK;
        return ETIMEDOUT;
    }

    while(1) {
        state = __sync_lock_test_and_set(c->m, 2);
        if (state == 0)
            return 0;
        int einval = syscall(SYS_futex, c->m, FUTEX_WAIT, 2, &deadlockTimeout, NULL, 0);
        assert(einval == 0 || (einval == -1 && (errno == EAGAIN || errno == ETIMEDOUT)));
        if (einval == -1 && einval == ETIMEDOUT)
            return EDEADLOCK;
    }
}

int cond_wait(condition *c, mutex *m) {
    return cond_timed_wait(c, m, NULL);
}

/**** Implementing Condition Variables using Spinlock ****/

int cond_wait_sl(condition *c, spinlock_t *sl) {
    //spinunlock(s);
    spinlock(&c->sl);
    c->count++; 
    spinunlock(&c->sl);
    spinunlock(sl);
    syscall(SYS_futex,&(c->sem.sl.val), FUTEX_WAIT_PRIVATE, 1, NULL, NULL, 0);
    spinlock(sl);
    return 0;

}

int cond_signal_sl(condition *c) {
    spinlock(&c->sl);
    c->count--;
    syscall(SYS_futex, &(c->sem.sl.val), FUTEX_WAKE_PRIVATE, 1, NULL, NULL, 0);
    spinunlock(&c->sl);
    return 0;
}

int cond_broadcast_sl(condition *c) {
    spinlock(&c->sl);
    while(c->count > 0) {
        syscall(SYS_futex, &(c->sem.sl.val), FUTEX_WAKE_PRIVATE, 1, NULL, NULL, 0);
        c->count--;
    }
    spinunlock(&c->sl);
    return 0;
}

