/*
Test sempahore with this code.
*/
#include <stdio.h>
#include <pthread.h>
#include<unistd.h>
#include "semaphore.h"
long c = 0, c1 = 0, c2 = 0, run = 1;
semaphore sem;
//pthread_mutex_t lock;

//mutex mut;
void *thread1(void *arg) {
	while(run == 1) {
		//spinlock(&l);
		wait(&sem);
		c++;
		signal(&sem);
		c1++;
	}
}
void *thread2(void *arg) {
	while(run == 1) {
		wait(&sem);
		c++;
		signal(&sem);
		c2++;
	}
}
int main() {
	pthread_t th1, th2;
	sem_init(&sem);
	pthread_create(&th1, NULL, thread1, NULL);
	pthread_create(&th2, NULL, thread2, NULL);
	sleep(2);
	//fprintf(stdout, "Ending main\n");
	run = 0;
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	fprintf(stdout, "c = %ld c1+c2 = %ld c1 = %ld c2 = %ld \n", c, c1+c2, c1, c2);
	fflush(stdout);
}
