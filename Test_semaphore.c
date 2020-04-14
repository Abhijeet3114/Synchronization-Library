/*
This is a non working solution to race problem
*/
#include <stdio.h>
#include <pthread.h>
#include"semaphore.c"
long c = 0, c1 = 0, c2 = 0, c3 = 0, run = 1;
int flag = 0;
pthread_mutex_t lock;
semaphore s;

void *thread1(void *arg) {
	while(run == 1) {
		//pthread_mutex_lock(&lock);
		wait(&s);
		c++;
		//pthread_mutex_unlock(&lock);
		signal(&s);
		c1++;
	}
}
void *thread2(void *arg) {
	while(run == 1) {
		//pthread_mutex_lock(&lock);
		wait(&s);
		c++;
		//pthread_mutex_unlock(&lock);
		signal(&s);
		c2++;
	}
}

void *thread3(void *arg) {
	while(run == 1) {
		//pthread_mutex_lock(&lock);
		wait(&s);
		c++;
		//pthread_mutex_unlock(&lock);
		signal(&s);
		c3++;
	}
}
int main() {
	pthread_t th1, th2, th3;
	sem_init(&s, 1);
	pthread_mutex_init(&lock, NULL);
	pthread_create(&th1, NULL, thread1, NULL);
	pthread_create(&th2, NULL, thread2, NULL);
	pthread_create(&th3, NULL, thread3, NULL);
	//fprintf(stdout, "Ending main\n");
	sleep(2);
	run = 0;
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);
	printf("c = %ld c1+c2+c3 = %ld c1 = %ld c2 = %ld c3 = %ld\n", c, c1+c2+c3, c1, c2, c3);
}
