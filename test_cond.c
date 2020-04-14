#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
//#include "spinlock.h"
#include "cond.h"


/* Compile like this:
 gcc --std=c99 -lpthread cond.c -o cond
*/

const size_t NUMTHREADS = 20;

/* a global count of the number of threads finished working. It will
   be protected by mutex and changes to it will be signalled to the
   main thread via cond */

int done = 0;
spinlock_t lk;
condition r;
mutex m;

/* Note: error checking on pthread_X calls ommitted for clarity - you
   should always check the return values in real code. */

/* Note: passing the thread id via a void pointer is cheap and easy,
 * but the code assumes pointers and long ints are the same size
 * (probably 64bits), which is a little hacky. */

void* ThreadEntry( void* id )
{
  const int myid = (long)id; // force the pointer to be a 64bit integer
  
  const int workloops = 5;
  for( int i=0; i<workloops; i++ )
    {
      printf( "[thread %d] working (%d/%d)\n", myid, i, workloops );
      sleep(1); // simulate doing some costly work
    }
  
  // we're going to manipulate done and use the cond, so we need the mutex
  spinlock(&lk);

  // increase the count of threads that have finished their work.
  done++;
  printf( "[thread %d] done is now %d. Signalling cond.\n", myid, done );

  // wait up the main thread (if it is sleeping) to test the value of done  
  cond_signal_sl( &r ); 
  spinunlock( &lk );

  return NULL;
}

int main( int argc, char** argv )
{
  puts( "[thread main] starting" );
  cond_init(&r);

  pthread_t threads[NUMTHREADS];

  for( int t=0; t<NUMTHREADS; t++ )
    pthread_create( &threads[t], NULL, ThreadEntry, (void*)(long)t );

  // we're going to test "done" so we need the mutex for safety
  spinlock(&lk);

  // are the other threads still busy?
  while( done < NUMTHREADS )
    {
      printf( "[thread main] done is %d which is < %d so waiting on cond\n", 
	      done, (int)NUMTHREADS );
      
      /* block this thread until another thread signals cond. While
	 blocked, the mutex is released, then re-aquired before this
	 thread is woken up and the call returns. */ 
      cond_wait_sl(&r,&lk); 
      
      puts( "[thread main] wake - cond was signalled." ); 
      
      /* we go around the loop with the lock held */
    }
  
  printf( "[thread main] done == %d so everyone is done\n", (int)NUMTHREADS );
  
  spinunlock(&lk);
  
  return 0;
}
