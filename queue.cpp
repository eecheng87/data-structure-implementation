//using array implement circular queue in C
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct{
	int data;
}queue;

//declare global variable
int capacity=5,size=0,front=0,rear=0;
queue *myQueue;
bool isEmpty();
bool isFull();
void push(int);
void pop();
void increaseCapacity();
int getFront();
int getRear();
int getSize();
int getCapacity();
int main(){
	myQueue = (queue*)malloc(sizeof(queue)*capacity);
	
//start to manipulate circular queue

	pop();
	push(10);
	printf("front:%d rear:%d size:%d capacity:%d\n",getFront(),getRear(),getSize(),capacity);
	push(20);
	printf("front:%d rear:%d size:%d capacity:%d\n",getFront(),getRear(),getSize(),capacity);
	push(30);
	printf("front:%d rear:%d size:%d capacity:%d\n",getFront(),getRear(),getSize(),capacity);
	push(40);
	printf("front:%d rear:%d size:%d capacity:%d\n",getFront(),getRear(),getSize(),capacity);
	push(50);
	printf("front:%d rear:%d size:%d capacity:%d\n",getFront(),getRear(),getSize(),capacity);
	pop(); 
	printf("front:%d rear:%d size:%d capacity:%d\n",getFront(),getRear(),getSize(),capacity);
	pop();
	pop();
	pop();
	printf("front:%d rear:%d size:%d capacity:%d\n",getFront(),getRear(),getSize(),capacity);
	pop();
	pop();
	return 0;
}
bool isEmpty(){
	if(front == rear)
		return TRUE;
	else
		return FALSE; 
}
bool isFull(){
	if( (rear+1)%capacity == front)
		return TRUE;
	else
		return FALSE;
}
void pop(){
	if(isEmpty()){
		printf("queue is already empty!\n");
	}
	else{
		front = (front+1)%capacity;
	}
}
void push(int new_member){
	if(isFull()){
		increaseCapacity();
	}
	myQueue[(++rear)%capacity].data = new_member;
		
}
void increaseCapacity(){
	int i;
 
	queue *new_queue = (queue*)malloc(capacity*2);
	for(i = 1;i <= getSize(); ++i){
		new_queue[i] = myQueue[(front+i)%capacity];
	}
	rear = getSize();
	front = 0;
	capacity = capacity * 2;
	free(myQueue);
	myQueue = new_queue;
	free(new_queue);
}
int getSize(){
	
	if(isEmpty())
		return 0;
	if(front<rear)
		return (rear-front);
	if(front>rear){
		size = capacity-(front-rear);
		return size;
	}
}
int getFront(){
	return myQueue[(front+1)%capacity].data;
}
int getRear(){
	return myQueue[rear].data;
}
