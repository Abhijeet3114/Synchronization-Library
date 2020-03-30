#include<linux/sched.h>
typedef struct node {
	struct task_struct process;
	struct node *next;
}node;
typedef struct list {
	node *head;
	node *tail;
}list;
void init(list *l);
void appendlist(list *l, struct task_struct Q);