# Synchronization-Library
What is done?
1. Spinlock
2. semaphores
3. condition variables
4. rwlock
5. mutex lock

Run ./test.sh to run test case per synchronization primitive Change persmissions by chmod 777 test.sh

1. spinlock : Test_spinlock.c 
testcase:
>$cc Test_spinlock.c -o try1 -lpthread  #compile
>$./try1  #execute
Example o/p:
c = 12644105 c1+c2 = 12644105 c1 = 5688085 c2 = 6956020

2. semaphores : Test_semaphore.c  (for counting semaphore only) and test_sem.c (for binary semaphore only)
testcase for counting semaphore:
>$cc Test_semaphore.c -o try -lpthread
>$./try
Exampele o/p:
c = 730745 c1+c2+c3 = 730745 c1 = 240257 c2 = 254757 c3 = 235731

3. condition variables
  testcase:
  1) For Testing Implementation using spinlock : test_cond.c
  2) For Tessting Iplemetation using mutex: test_cond_mutex.c
  Example o/p in condition_test.txt

4. Mutex Implementation:
  Mutex lock and unlock.Mutex will also unlock on timeout.

5. ReadWriteLocks:
  1) Testing using mutex-lock and unlock: rwtest_new_mutex.c
  2) Testing using spinlock spinunlock: rwtest_new.c
  Expected output in rwtest.txt
