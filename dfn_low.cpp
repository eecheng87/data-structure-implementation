#include<stdio.h>
#include<stdlib.h>
#define MIN2(x,y) ((x)<(y)? (x):(y))
#define n 10
typedef struct Node node;
typedef struct Node{
	int vertex;
	node* link;
};
node* graph[n];
int dfn[n];
int low[n];
int visited[n];
int num;
void dfnlow(int u,int v){
	node* ptr;
	int w;
	dfn[u] = low[u] = num++;
	for(ptr=graph[u]->link;ptr;ptr=ptr->link){
		w = ptr->vertex;
		if(dfn[w]<0){
			dfnlow(w,u);
			low[u] = MIN2(low[u],low[w]);
		}
		else if(w!=v){
			low[u] = MIN2(low[u],dfn[w]);
		}
	}
}
void init(){
	int i;
	for(i=0;i<n;i++){
		graph[i] = (node*)malloc(sizeof(node*));
		graph[i]->link = NULL;
		visited[i]=0;
		dfn[i] = low[i] = -1;
	}
	num=0;
}
void add(int index,int myvertex){
	node* tmp = (node*)malloc(sizeof(node*));
	node* flag;
	node* head;
	for(head = graph[index]; head ; head = head->link){
		flag = head;
	}
	tmp->vertex = myvertex;
	tmp->link = NULL;
	flag->link = tmp;
}
int main(){
 
	init();
	add(3,4);
	add(3,1);
	add(3,5);
	add(4,3);
	add(4,2);
	add(2,4);
	add(2,1);
	add(1,2);
	add(1,3);
	add(1,0);
	add(0,1);
	add(5,3);
	add(5,6);
	add(5,7);
	add(6,7);
	add(6,5);
	add(7,5);
	add(7,6);
	add(7,9);
	add(7,8);
	add(8,7);
	add(9,7);
 
	dfnlow(3,-1);
 
	int i;
	for(i=0;i<10;i++)
		printf("%d %d\n",dfn[i],low[i]);
 
}
