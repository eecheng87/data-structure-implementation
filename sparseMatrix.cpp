#include<stdlib.h>
#include<stdio.h>
#define MaxHeadLength 50
//declare global structure for sparseMatrix using linked list 
typedef enum{ head, entry
}flag;
typedef struct sparseNode Node;
typedef struct entryNode{
	int row;
	int col;
	int value;
}; 
typedef struct sparseNode{
	Node *right;
	Node *down;
	flag tag;
	union{
		Node *next;
		entryNode entry;
	}u;
};
//declare global head
Node *headNode[MaxHeadLength];
//implemeny two function: read and write
Node* read();
void write(Node*);

int main(){
	Node *myMatrix;
	//myMatrix = read();

	return 0;
}

Node *read(){
	Node *tmp;
	Node *node;
	Node *last; // flag for row list
	int numHead, numRow, numCol, term, i;
	int row, col, value;
	numRow=5;
	numCol=4;
	term=6;
	//printf("Enter row, colunm, nonzero term in order\n");
	//scanf("%d%d%d",&numRow,&numCol,&term);
	numHead = numRow>numCol?numRow:numCol;
	if(numHead>MaxHeadLength){
		printf("too many rows or columns");
		return 0;
	}
	//initial Node node
	node = (Node*)malloc(sizeof(Node*));
	node->tag = entry;
	node->u.entry.col = numCol;
	node->u.entry.row = numRow;
	node->u.entry.value = term;
	//initial each head
	for(i = 0; i < numHead; ++i){
		tmp = (Node*)malloc(sizeof(Node*));
		headNode[i] = tmp;
		headNode[i]->tag = head;
		headNode[i]->u.next = tmp;
		headNode[i]->down = tmp;
		headNode[i]->right = tmp; 	
	}
	//start to read element
	last = headNode[0];
	int currentRow = 0;
	for(i = 0; i < term; ++i){
		printf("Enter row, col, value");
		scanf("%d%d%d",&row,&col,&value);
		tmp = (Node*)malloc(sizeof(Node*));
		 
		if(row > currentRow){
			last->right = headNode[currentRow];
			currentRow = row;
			last = headNode[row];
		}
		//create tmp node
		tmp->tag = entry;
		tmp->u.entry.col = col;
		tmp->u.entry.row = row;
		tmp->u.entry.value = value;
		//link row
		last->right = tmp;
		last = tmp;
		//link col list
		//next is store tmp which is last in each col
		headNode[col]->u.next = tmp;
		headNode[col]->u.next->down = tmp;
	}
	//finish last row's last node link to last row's head
	last->right = headNode[currentRow];
	//using flag next which store last tmp in each col to link ROW LINK
	for(i = 0; i < numHead; ++i){
		headNode[i]->u.next->down = headNode[i];
	}
	//link each headNode
	for(i = 0; i < numHead-1; ++i){
		headNode[i]->u.next = headNode[i+1];
	}
	headNode[i]->u.next = node;
	node->right = headNode[0];
	return node;
}
void write(Node* node){
	
	
}
