#include <stdio.h>
#include <pthread.h>
#include<unistd.h>
#include"spinlock.c"
long c = 0, c1 = 0, c2 = 0, run = 1;
int flag = 0;
spinlock_t sl;	//spinlock initialization
void *thread1(void *arg) {
	while(run == 1) {
		spinlock(&(sl));	//lock
		c++;
		spinunlock(&(sl));	//unlock
		c1++;
	}
}
void *thread2(void *arg) {
	while(run == 1) {
		spinlock(&(sl));	//lock
		c++;
		spinunlock(&(sl));		//unlock
		c2++;
	}
}
int main() {
	pthread_t th1, th2;
	pthread_create(&th1, NULL, thread1, NULL);
	pthread_create(&th2, NULL, thread2, NULL);
	sleep(2);
	run = 0;
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	fprintf(stdout, "c = %ld c1+c2 = %ld c1 = %ld c2 = %ld \n", c, c1+c2, c1, c2);
	fflush(stdout);
}
