//using array implement stack in solving 2*2 maze puzzle, coordinate is (row,col)
#include<iostream>
#include<stdlib.h>
using namespace std;
#define TRUE 1
#define FALSE 0
#define EXIT_ROW 3
#define EXIT_COL 4
typedef struct{
	int vert;
	int horiz;
}offsets;
typedef struct{
	int row;
	int col;
	int dir;
}element;
offsets move[4];


class ArrayStack{
	public:
		ArrayStack(){
			size = 20;
			top = -1;
			stack = (element*)malloc(sizeof(element)*size);
		}
		int size;
		int top;
		element *stack;
		bool isEmpty();
		void push(int,int);
		void pop();
		int getSize();
		int getTop();
};
void ArrayStack::push(int row,int col){
	top++;
	size++;
	stack[top].col = col;
	stack[top].row = row;
	
}
void ArrayStack::pop(){
	if(top == -1) {
		cout<<"Stack is empty";
		return;	
	}
	top--;
}
int ArrayStack::getSize(){
	return size;
}
int ArrayStack::getTop(){
	return top;
}
bool ArrayStack::isEmpty(){
	if(top==-1)
		return TRUE;
	else
		return FALSE;
		
}

int main(){
	int i=-1;
	bool found=FALSE;
	move[0].horiz=0,move[0].vert=-1,
	move[1].horiz=1,move[1].vert=0,
	move[2].horiz=0,move[2].vert=1,
	move[3].horiz=-1,move[3].vert=0;
	int maze[5][6]={{1,1,1,1,1,1},{1,0,0,0,0,1},{1,1,0,1,1,1},{1,1,0,0,0,1},{1,1,1,1,1,1}};
	int map[5][6]={{1,1,1,1,1,1},{1,0,0,0,0,1},{1,0,0,0,0,1},{1,0,0,0,0,1},{1,1,1,1,1,1}};
	
	ArrayStack myStack;
	//start to try
	myStack.push(1,1);
	while(!found){
		int next_row,next_col;
		i = 0;//decide offsets' index		
		while(i<4){
			next_row = myStack.stack[myStack.getTop()].row + move[i].vert;
		    next_col = myStack.stack[myStack.getTop()].col + move[i].horiz;
		    if(next_col == EXIT_COL && next_row == EXIT_ROW){
				found = TRUE;
			}
			if(map[next_row][next_col]==0 && maze[next_row][next_col]==0){
			myStack.push(next_row,next_col);
			map[next_row][next_col] = 1;
			i = 0;//reset offsets' index	
			}else{
				i++;
			}
		}
		myStack.pop();
	}
	
	if(found){
		for(int j=0 ; j<=myStack.getTop() ; ++j){
			cout<<"("<<myStack.stack[j].row<<","<<myStack.stack[j].col<<")\n";
		}
	}else{
		cout<<"the maze is unsolvable!\n";
	}
	cout<<"("<<EXIT_ROW<<","<<EXIT_COL<<")\n";
	return 0;
}


