#! /bin/bash

while true
do
	echo -e "Enter Synchronization Primitive Number You Want to Test :- \n"
	echo -e "(1) Spinlock \n"
	echo -e "(2) Semaphore \n"
	echo -e "(3) Condition Varibale using Spinlock \n"
	echo -e "(4) Condition Variable using Mutex lock-unlock \n"
	echo -e "(5) Read Write Locks using Spinlock \n"
	echo -e "(6) Read Write Locks using Mutex lock-unlock \n"
	read num
	case $num in 
	1)
	gcc Test_spinlock.c -lpthread
	./a.out
	;;
	2)
	gcc test_sem.c -lpthread
	./a.out
	;;
	3)
	gcc test_cond.c -lpthread
	./a.out
	;;
	4)
	gcc test_cond_mutex.c -lpthread
	./a.out
	;;
	5)
	gcc rwtest_new.c -lpthread
	./a.out
	;;
	6)
	gcc rwtest_new_mutex.c -lpthread
	./a.out
	;;
	esac

	echo -e "Do you want to continue?(y/n)"
	read ans
	if [ $ans == 'y' ]
	then
		continue
	else
		break
	fi
done
