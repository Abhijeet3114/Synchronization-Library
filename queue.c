#include"queue.h"
#include<stdio.h>
#include<stdlib.h>

void qinit(list *l) {
	l -> head = NULL;
	l -> tail = NULL;
	l -> tail = l->head;
	l -> count = 0;
}
void enq(list *l, struct task_struct curr) {
	node *p;
	p = (node*)malloc(sizeof(node));
	p -> process = curr;  
	if(l -> head == NULL && l -> tail == NULL) {
		l -> head = p;
		l -> tail = p;
	}
	l -> tail -> next  = p;
	l -> tail = p;
	(l -> count)++;
}
struct task_struct deq(list *l) {
	node *p;
	struct task_struct x;
	x = l -> head -> val ;
	p = l -> head;
	l -> head = l -> head -> next;
	free(p);
	(l -> count)--;
	return x;
}
int isempty(list *l) {
	l -> head = l -> tail;
	return l -> count == 0;
}


	
	
	
	
		
	
	