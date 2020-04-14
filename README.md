# Synchronization-Library
What is done?
1. Spinlock
2. semaphores
3. condition variables
4. rwlock
5. mutex lock

1. spinlock
testcase:
>$cc Test_spinlock.c -o try1 -lpthread  #compile
>$./try1  #execute
c = 12644105 c1+c2 = 12644105 c1 = 5688085 c2 = 6956020

2. semaphores
testcase:
>$cc Test_semaphore.c -o try -lpthread
>$./try
c = 730745 c1+c2+c3 = 730745 c1 = 240257 c2 = 254757 c3 = 235731
>$
