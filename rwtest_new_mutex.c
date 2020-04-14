#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>


#include "rwlock_mutex.h"



rwlock r;

void* reader(void* arg)
{
    printf("Obtaining read lock.\n");

    lockShared(&r);
   
    printf( "Obtained read lock.\n");

    sleep(5);

    printf( "Releasing read lock.\n");

    unlockShared(&r);

    printf( "Released read lock.\n");   
}


void* writer(void* arg)
{
    printf( "Obtaining write lock.\n");

   lockExclusive(&r);
   
    printf( "Obtained write lock.\n");

    sleep(4);

    printf( "Releasing write lock.\n");

    unlockExclusive(&r);

    printf( "Released write lock.\n");   
}

int main(int argc, char** argv)
{
    pthread_t r1,r2,r3,w1,w2;

    int res;

    printf("\n");   

    res = pthread_create(&r1, NULL, reader, NULL);

    if(0 != res)
    {
        printf( "Failed to start thread.\n");
        exit(1);
    }
           
    res = pthread_create(&r2, NULL, reader, NULL);

    if(0 != res)
    {
        printf( "Failed to start thread.\n");
        exit(1);
    }           

    sleep(1);

    res = pthread_create(&w1, NULL, writer, NULL);

    if(0 != res)
    {
        printf( "Failed to start thread.\n");
        exit(1);
    }   

    res = pthread_create(&w2, NULL, writer, NULL);

    if(0 != res)
    {
        printf( "Failed to start thread.\n");
        exit(1);
    }   
    pthread_exit(NULL);       
}
