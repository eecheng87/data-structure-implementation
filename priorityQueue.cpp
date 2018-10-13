// using c to implement priority queue and this version is mini-priority-queue
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct Node{
	int data;
	int weight;
	Node* next;
};
Node* newNode(int,int);
void push(Node**,int,int);
void pop(Node**);
int top(Node**);
bool isEmpty(Node**);

int main() 
{ 
    // Create a minimun Priority Queue 
    // 7->4->5->6 
    Node* pq = newNode(4, 1); 
    push(&pq, 5, 2); 
    push(&pq, 6, 3); 
   // push(&pq, 7, 0); 
  
    while (!isEmpty(&pq)) { 
        printf("%d ", top(&pq)); 
        pop(&pq); 
    } 
  
    return 0; 
} 

Node* newNode(int d,int w){
	
	Node* tmp = (Node*)malloc(sizeof(Node*));
	tmp->data = d;
	tmp->weight = w;
	tmp->next = NULL;
	return tmp;
}
void pop(Node** head){
	Node* tmp = (*head);
	(*head) = (*head)->next;
	free(tmp);
}
void push(Node** head,int d,int w){
	
	Node* tmp = newNode(d,w);
	Node* start = *head;/* it is improtant temp variable for while loop, if we use 
							*head, the while loop will crash, because it will
							change the *head which pass into the function*/
							
	//if new node is smallest
	if(w < (*head)->weight){
		tmp->next = (*head);
		(*head) = tmp;
		return;
	}
	while(start->next!=NULL && tmp->weight>start->next->weight){// if *head->next is null, it means head now is last node 
		start = start->next;
	}
	tmp->next = start->next;
	start->next = tmp;
	
}

int top(Node** head){
	return (*head)->data;
}

bool isEmpty(Node** head){
	if((*head) == NULL)
		return TRUE;
	else 
		return FALSE;
}


