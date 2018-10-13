// this program is using Dijkstra's algorithmn
// weight is stored as adjacency matrix
#include<stdio.h>
#include<stdlib.h>
#define INF 10000000
#define TRUE 1
#define FALSE 0
int weight[6][6];//weight between a and b
int d[6];//d[index] means node SOURCE to node index' path
int parent[6];
int visited[6];//if value is zero means unvisited
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
	
	//ps: this algorithmn is different from previos, it should predefine d[] which is connected by SOURCE
	parent[0] = 0;
	parent[2] = 0;
	parent[3] = 0;
	parent[1] = 0;
	d[0] = 0;
	/*d[1] = 50;
	d[2] = 45;
	d[3] = 10;*/
	
}
void Dijkstra(int source){
	
	int a, b, min;
	int i, j, k;

	for(i = 0; i < 6; i++){// iterate 6 times
		min = INF;
		a = -1;
		for(j = 0; j < 6; j++){
			if(!visited[j] && d[j] < min){
				a = j; // it like a flag to memorize which node is closest to SOURCE
				min = d[j];
			}
		}
		
		if(a < 0)
			return;
			
		visited[a] = TRUE;
		
		for(k = 0; k < 6; k++){
			if(!visited[k] && (d[a] + weight[a][k] < d[k])){
				d[k] = d[a] + weight[a][k];
				parent[k] = a;
			}
		}
		
	}
}









