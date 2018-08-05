//use singly linkedlist to implement multiple stack in C
#include<stdio.h>
#include<stdlib.h>
#define num 3
typedef struct listNode Node;
typedef struct listNode{
	int data;
	struct listNode* next;
};

Node *top[num]; //declare multi head
int pop(int);
void push(int,int);
void printList(int);
int main(){
	
//start to manipulate multiple stack
	pop(1);
	push(1,10);
	push(1,20);
	push(1,30);
	pop(1);
	push(0,11);
	push(0,12);
	printList(0);
		
	return 0;
} 
int pop(int i){
	
	if(top[i] == NULL){
		printf("list[%d] is already empty!\n",i);
	}
	else{
		Node *tmp = top[i];
		int tmp_data = tmp->data;
		top[i] = top[i]->next;
		free(tmp);
		return tmp_data;
	}
}
void push(int i,int new_data){
	
	Node* insert = (Node*)malloc(sizeof(Node*));
	insert->data = new_data;
	insert->next = top[i];
	top[i] = insert;
	
}
void printList(int i){
	Node *tmp = top[i];
	int k;
	for(;tmp->next!=NULL;tmp=tmp->next){
		printf("%d\n",tmp->data);
	}
	printf("%d\n",tmp->data);
}
