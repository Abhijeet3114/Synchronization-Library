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

typedef int mutex;

 void mutex_init(mutex *m);
 int mutex_timed_lock(mutex *m, const struct timespec *timeout);
 int mutex_lock(mutex *m);
 void mutex_unlock(mutex *m);


 void mutex_init(mutex *m) {
    *m = 0;
 }

int mutex_timed_lock(mutex *m, const struct timespec *timeout) {
 
    int state = __sync_val_compare_and_swap(m, 0, 1);
    if (state == 0)
        return 0;

    while(1) {
        state = __sync_lock_test_and_set(m, 2);
        if (state == 0)
            return 0;
        int einval = syscall(SYS_futex, m, FUTEX_WAIT, 2, timeout, NULL, 0);

        assert(einval == 0 || (einval == -1 && (errno == EAGAIN || errno == ETIMEDOUT)));
        if (einval == -1 && errno == ETIMEDOUT)
            return ETIMEDOUT;
    }
}
int mutex_lock(mutex *m) {
    struct timespec deadlockTimeout = {10 + 2, 0};

    return mutex_timed_lock(m, &deadlockTimeout) == ETIMEDOUT ? EDEADLOCK : 0;
}

 void mutex_unlock(mutex *m) {
    int state;

    state = __sync_lock_test_and_set(m, 0);

    if (state == 1)
        return;
    syscall(SYS_futex, m, FUTEX_WAKE, 1, NULL, NULL, 0);
}

