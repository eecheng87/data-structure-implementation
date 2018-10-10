//this program is for searching the least path of one SOURCE to each node in the tree

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
void shortpath(int);//parameter is the index of the SOURCE
void printResult();
int main(){
	init();
	shortpath(0);
	printResult();
	return 0;
}
void init(){
	int i,j;
	for(i = 0; i < 6; i++){
		visited[i] = FALSE;
		parent[i] = -1;
		d[i] = -1;
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
}
void printResult(){
	int i;
	for(i = 0; i < 6; i++)
		if(d[i]>0)
			printf("The shortest distance to node %d is %d\n",i,d[i]);
		else
			printf("There is no path connect SOURCE to node %d\n",i);
}
void shortpath(int source){
	
	visited[source] = TRUE;
	parent[source] = 0;
	d[source] = 0;
	
	int a, b, min;
	int i, j, k;
	
	for(i = 0; i < 4; i++){
		a = b = min = INF;
		for(j = 0; j < 6; j++){
			if(visited[j]){
				for(k = 0; k < 6; k++){
					if(!visited[k]){
						if(d[j]+weight[j][k]<min){
							min = d[j] + weight[j][k];
							a = j;
							b = k;//memorize two node
						}
					}
				}
			}
		}
		if(a==b==INF)
			break;
		parent[b] = a;
		d[b] = min;
		visited[b] = TRUE;
	}
	
	
}

















