#include<stdio.h>
#include<linux/sched.h>
typedef struct node {
	struct task_struct process;
	struct node *next;
}node;
typedef struct que {
	int count;
	node *head;
	node *tail;
}que;
void qinit(list *l);
void enq(list *l, int val);
int deq(list *l);
int isempty(list *l);