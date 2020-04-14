# Synchronization-Library
What is done?
1. Spinlock
2. semaphores
3. condition variables
4. rwlock
5. mutex lock

1. spinlock : Test_spinlock.c
testcase:
>$cc Test_spinlock.c -o try1 -lpthread  #compile
>$./try1  #execute
Example o/p:
c = 12644105 c1+c2 = 12644105 c1 = 5688085 c2 = 6956020

2. semaphores : Test_semaphore.c 
testcase:
>$cc Test_semaphore.c -o try -lpthread
>$./try
Exampele o/p:
c = 730745 c1+c2+c3 = 730745 c1 = 240257 c2 = 254757 c3 = 235731

3.condition variables
testcase:
1)For Testing Implementation using spinlock : test_cond.c
2)For Tessting Iplemetation using mutex: test_cond_mutex.c
Example o/p:
[thread main] starting
[thread 1] working (0/5)
[thread 0] working (0/5)
[thread 2] working (0/5)
[thread 3] working (0/5)
[thread 5] working (0/5)
[thread 4] working (0/5)
[thread 6] working (0/5)
[thread 7] working (0/5)
[thread 8] working (0/5)
[thread 9] working (0/5)
[thread 10] working (0/5)
[thread 11] working (0/5)
[thread 12] working (0/5)
[thread 13] working (0/5)
[thread 14] working (0/5)
[thread 15] working (0/5)
[thread 16] working (0/5)
[thread 17] working (0/5)
[thread main] done is 0 which is < 20 so waiting on cond
[thread 18] working (0/5)
[thread 19] working (0/5)
[thread 5] working (1/5)
[thread 8] working (1/5)
[thread 14] working (1/5)
[thread 6] working (1/5)
[thread 17] working (1/5)
[thread 4] working (1/5)
[thread 7] working (1/5)
[thread 3] working (1/5)
[thread 10] working (1/5)
[thread 9] working (1/5)
[thread 13] working (1/5)
[thread 1] working (1/5)
[thread 12] working (1/5)
[thread 11] working (1/5)
[thread 2] working (1/5)
[thread 15] working (1/5)
[thread 16] working (1/5)
[thread 0] working (1/5)
[thread 19] working (1/5)
[thread 18] working (1/5)
[thread 5] working (2/5)
[thread 14] working (2/5)
[thread 8] working (2/5)
[thread 6] working (2/5)
[thread 4] working (2/5)
[thread 17] working (2/5)
[thread 3] working (2/5)
[thread 7] working (2/5)
[thread 10] working (2/5)
[thread 9] working (2/5)
[thread 13] working (2/5)
[thread 1] working (2/5)
[thread 12] working (2/5)
[thread 11] working (2/5)
[thread 2] working (2/5)
[thread 15] working (2/5)
[thread 16] working (2/5)
[thread 0] working (2/5)
[thread 19] working (2/5)
[thread 18] working (2/5)
[thread 5] working (3/5)
[thread 6] working (3/5)
[thread 1] working (3/5)
[thread 8] working (3/5)
[thread 17] working (3/5)
[thread 3] working (3/5)
[thread 12] working (3/5)
[thread 7] working (3/5)
[thread 13] working (3/5)
[thread 10] working (3/5)
[thread 9] working (3/5)
[thread 4] working (3/5)
[thread 14] working (3/5)
[thread 16] working (3/5)
[thread 11] working (3/5)
[thread 0] working (3/5)
[thread 15] working (3/5)
[thread 19] working (3/5)
[thread 18] working (3/5)
[thread 2] working (3/5)
[thread 5] working (4/5)
[thread 6] working (4/5)
[thread 8] working (4/5)
[thread 17] working (4/5)
[thread 13] working (4/5)
[thread 9] working (4/5)
[thread 12] working (4/5)
[thread 7] working (4/5)
[thread 10] working (4/5)
[thread 16] working (4/5)
[thread 1] working (4/5)
[thread 4] working (4/5)
[thread 3] working (4/5)
[thread 11] working (4/5)
[thread 14] working (4/5)
[thread 15] working (4/5)
[thread 0] working (4/5)
[thread 19] working (4/5)
[thread 18] working (4/5)
[thread 2] working (4/5)
[thread 5] done is now 1. Signalling cond.
[thread main] wake - cond was signalled.
[thread main] done is 1 which is < 20 so waiting on cond
[thread 6] done is now 2. Signalling cond.
[thread 8] done is now 3. Signalling cond.
[thread main] wake - cond was signalled.
[thread main] done is 3 which is < 20 so waiting on cond
[thread 17] done is now 4. Signalling cond.
[thread 9] done is now 5. Signalling cond.
[thread 11] done is now 6. Signalling cond.
[thread 3] done is now 7. Signalling cond.
[thread 14] done is now 8. Signalling cond.
[thread 12] done is now 9. Signalling cond.
[thread 19] done is now 10. Signalling cond.
[thread 1] done is now 11. Signalling cond.
[thread 10] done is now 12. Signalling cond.
[thread 4] done is now 13. Signalling cond.
[thread main] wake - cond was signalled.
[thread main] done is 13 which is < 20 so waiting on cond
[thread 13] done is now 14. Signalling cond.
[thread main] wake - cond was signalled.
[thread main] done is 14 which is < 20 so waiting on cond
[thread 0] done is now 15. Signalling cond.
[thread 16] done is now 16. Signalling cond.
[thread main] wake - cond was signalled.
[thread main] done is 16 which is < 20 so waiting on cond
[thread 2] done is now 17. Signalling cond.
[thread 15] done is now 18. Signalling cond.
[thread 18] done is now 19. Signalling cond.
[thread 7] done is now 20. Signalling cond.
[thread main] wake - cond was signalled.
[thread main] done == 20 so everyone is done

4.Mutex Implementation:
Mutex lock and unlock.Mutex will also unlock on timeout.

5.ReadWriteLocks:
Testing using mutex-lock and unlock: rwtest_new_mutex.c
Testing using spinlock spinunlock: rwtest_new.c
Expected output:-
Obtaining read lock.
Obtained read lock.
Obtaining read lock.
Obtained read lock.
Obtaining write lock.
Obtaining write lock.
Releasing read lock.
Released read lock.
Releasing read lock.
Released read lock.
Obtained write lock.
Releasing write lock.
Released write lock.
Obtained write lock.
Releasing write lock.
Released write lock.

