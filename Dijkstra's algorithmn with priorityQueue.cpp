// the program is using C to implement Dijkstra's algorithmn 
// also, we use min Priority Queue inside Dijkstra function
// using adjacency matrix

#include<stdio.h>
#include<stdlib.h>
#define INF 10000000
#define TRUE 1
#define FALSE 0
typedef struct Node{
	int data;
	int distance;
	Node* next;
};

int weight[6][6];//weight between a and b
int d[6];//d[index] means node SOURCE to node index' path
int parent[6];
int visited[6];//if value is zero means unvisited

//PQ
Node* newNode(int,int);
void push(Node**,int,int);
void pop(Node**);
int top(Node**);
bool isEmpty(Node**);

//Dijkstra
void init();
void Dijkstra(int);//parameter is the index of the SOURCE
void printResult(int);


int main(){
	init();
	Dijkstra(0);
	
	printf("The path of SOURCE to node 1 :");
	printResult(1);
	printf("it cost distance %d\n",d[1]);
	printf("The path of SOURCE to node 2 :");
	printResult(2);
	printf("it cost distance %d\n",d[2]);
	printf("The path of SOURCE to node 3 :");
	printResult(3);
	printf("it cost distance %d\n",d[3]);
	printf("The path of SOURCE to node 4 :");
	printResult(4);
	printf("it cost distance %d\n",d[4]);
	
	return 0;
}
//following code is for priority queue
Node* newNode(int d,int w){
	
	Node* tmp = (Node*)malloc(sizeof(Node*));
	tmp->data = d;
	tmp->distance = w;
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
	if(w < (*head)->distance){
		tmp->next = (*head);
		(*head) = tmp;
		return;
	}
	while(start->next!=NULL && tmp->distance>start->next->distance){// if *head->next is null, it means head now is last node 
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
//following code is for Dijkstra's algorithmn
void printResult(int destination){
	if(destination != parent[destination])
		printResult(parent[destination]);
	printf("%d ",destination);
	
}
void init(){
	int i,j;
	for(i = 0; i < 6; i++){
		visited[i] = FALSE;
		parent[i] = -1;
		d[i] = INF;
	}
	for(i = 0; i < 6; i++)
		for(j = 0; j < 6; j++)
			weight[i][j] = INF;
	
	weight[0][1] = 50;
	weight[0][2] = 45;
	weight[0][3] = 10;
	weight[1][2] = 10;
	weight[1][3] = 15;
	weight[2][4] = 30;
	weight[3][0] = 20;
	weight[3][4] = 15;
	weight[4][1] = 20;	
	weight[4][2] = 35;
	weight[5][4] = 3;
	
	//ps: this algorithmn is different from previous, it should predefine d[] which is connected by SOURCE
	parent[0] = 0;
	parent[2] = 0;
	parent[3] = 0;
	parent[1] = 0;
}
void Dijkstra(int source){
	
	int i, j;
	int a, b;
	
	parent[source] = 0;
	d[source] = 0;
	Node* pq = newNode(0,0);
	
	for(i = 0; i < 6; i++){
		a = -1;
		while(!isEmpty(&pq) && visited[a = top(&pq)]){
			pop(&pq);
		}
		
		if(a == -1)
			break;
		
		visited[a] = TRUE;
		
		for(j = 0; j < 6; j++){
			if(!visited[j] && weight[a][j] + d[a] < d[j]){//unvisited
				d[j] = d[a] + weight[a][j];
				parent[j] = a;
				push(&pq,j,d[j]);
			}
		}
	}
}

