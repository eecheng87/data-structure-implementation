// using array implement stack in C++
#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
class ArrayStack{
	public:
		ArrayStack(){
			size = 1;
			top = -1;
			stack = new int[size];
		}
		int size;
		int top;
		int *stack;
		void increaseSize();
		bool isEmpty();
		void push(int);
		void pop();
		void printMember();
		int getSize();
		int getTop();
};
void ArrayStack::push(int new_element){
	top++;
	if(top >= size){
		increaseSize();
		stack[top] = new_element;
	}
	else{
		size++;
		stack[top] = new_element;
	}
}
void ArrayStack::pop(){
	if(top == -1) {
		cout<<"Stack is empty";
		return;	
	}
	top--;
}
void ArrayStack::increaseSize(){
	size = size * 2;
	int *new_stack = new int[size];
	
	for(int i = 0 ; i < size/2 ; ++i){
		new_stack[i] = stack[i];
	}
	delete [] stack;
	stack = new_stack;
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
void ArrayStack::printMember(){
	for(int i = 0; i <= top; ++i)
		cout<<stack[i]<<" ";
}
int main(){
	ArrayStack myStack;

	myStack.push(10);
	myStack.push(20);
	myStack.push(30);
	myStack.pop();
	myStack.push(10);
	myStack.printMember();
	return 0;
}
