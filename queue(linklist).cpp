//use singly linkedlist to implement multiple queue in C
#include<stdio.h>
#include<stdlib.h>
#define num 3
typedef struct listNode Node;
typedef struct listNode{
	int data;
	struct listNode* next;
};
void push(int,int);
void pop(int);
void printList(int);
Node *front[num];
Node *rear[num];
int main(){
	
	push(1,10);
	push(1,20);
	pop(1);
	push(1,30);
	printList(1);
	
	return 0;
}
void push(int i,int new_data){
	
	if(front[i] == NULL){
		front[i] = (Node*)malloc(sizeof(Node*));
		front[i]->data = new_data;
		//front[i]->next = NULL;
		rear[i] = front[i];
	}
	else{
		Node *tmp = (Node*)malloc(sizeof(Node*));
		tmp->data = new_data;
		tmp->next = NULL;
		rear[i]->next = tmp;
		rear[i] = tmp;	
	}
}
void pop(int i){
	
	if(front[i] == NULL){
		printf("queue[%d] is already empty\n",i);
	}
	else{
		Node *tmp = front[i];
		front[i] = front[i]->next;
		free(tmp);
	}
}
void printList(int i){
	Node *tmp = front[i];
	for(;tmp->next != NULL;tmp=tmp->next){
		printf("%d\n",tmp->data);	
	}
	printf("%d\n",tmp->data);
}
