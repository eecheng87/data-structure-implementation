//use linkedlist to implement adding polynorphism
//implement a+b=c
//in this code, also contain use getNode() to get node from 'avail' list
#include<stdlib.h>
#include<stdio.h>
#define TRUE 1;
#define FALSE 0;
struct polyNode{
	int coef;
	int exp;
	struct polyNode *next;
};
typedef struct polyNode Node;
void initial(int,int,Node**);
Node* add(Node*,Node*,Node**);
Node* getNode();
void attach(int,int,Node**);
void printPoly(Node*);
int compare(int,int);
Node* avail = (Node*)malloc(sizeof(Node*));
int main(){

	Node *a=NULL;
	Node *b=NULL;
	Node *ans=NULL;
	initial(3,14,&a);
	initial(2,8,&a);
	initial(1,0,&a);
	//printPoly(a);
	initial(2,10,&b);
	initial(9,8,&b);
	initial(2,1,&b);
	//printPoly(b);

	printPoly(add(a,b,&ans));
	return 0;
}
void printPoly(Node *head){
	for(head=head->next;head->next->exp>=0;head=head->next)
		printf("%d*X^%d+",head->coef,head->exp);
		printf("%d*X^%d",head->coef,head->exp);
		printf("\n");
}
Node* getNode(){//have bug, fix later
	/*if(avail==NULL){
		return (Node*)malloc(sizeof(Node*));
	}
	else{
		Node* temp = avail;
		avail = avail->next;
		return avail;
	}*/
}
void initial(int coefficient,int exponent,Node **head){
	Node* polyNode = (Node*)malloc(sizeof(Node*));
	polyNode->coef = coefficient;
	polyNode->exp = exponent;

	if( (*head)==NULL ){//if is void list, add head and current node
		*head = (Node*)malloc(sizeof(Node*));
		(*head)->exp = -1;
		(*head)->next = polyNode;
		polyNode->next = (*head);	
	}
	else{
		Node *tmp = *head;
		while(1){
			if(tmp->next->exp<0){
				
				break;
			}
			else{
				tmp = tmp->next;
			}
		}
		tmp->next = polyNode;
		polyNode->next = (*head);
	}
}
int compare(int a,int b){
	return a>b?1:a<b?-1:0; // a==b return 0, a<b return -1, a>b return 1
}
Node* add(Node *a,Node *b,Node **c){
	int tmp_coe;
	int tmp_exp;
	a = a->next;
	b = b->next;
	int finish = FALSE;
	while(!finish){
		switch(compare(a->exp,b->exp)){
			case 1://a>b
				initial(a->coef,a->exp,c);
				a = a->next;
				break;
			case 0://a==b
				if(a->exp == -1){
					finish = TRUE;
				}
				initial(a->coef+b->coef,a->exp,c);
				a = a->next;
				b = b->next;
				break;
			case -1://a<b
				initial(b->coef,b->exp,c);
				b = b->next;
				break;
		}	
	}
	return *c;
}
