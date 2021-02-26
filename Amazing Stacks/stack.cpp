/****************************************************************************************
Name: stack.cpp
Description: This file contains the implementations of the constructor, destructor, 
				empty, push, and pop functions used with a stack ADT.
Author: Caleb Manor
****************************************************************************************/

#include <iostream>
#include "stack.h"

using namespace std;

/****************************************************************************************
CONSTRUCTOR - Creates an empty stack by assigning the top of the stack to NULL
****************************************************************************************/

Stack::Stack() : top(nullptr) {}

/****************************************************************************************
DESTRUCTOR - Deletes the entirety of the stack
****************************************************************************************/

Stack::~Stack() {

	Node * current = top;

	while (top != nullptr) {
		current = top->next;
		delete top;
		top = current;
	}

}

/****************************************************************************************
Function: Empty
Description: Function will check to see if the stack is empty or not
****************************************************************************************/

bool Stack::Empty() {

	if (top == nullptr)
		return true;
	else
		return false;

}

/****************************************************************************************
Function: Push
Description: Function will push a move from the maze onto the top of the stack. If
				memory is not allocated, the function will return false. 
****************************************************************************************/

bool Stack::Push(Coordinate pushedMove) {

	Node * newMove = new Node;
	if (newMove == nullptr)
		return false;

	newMove->position = pushedMove;
	newMove->next = top;
	top = newMove;

	return true;

}

/****************************************************************************************
Function: Pop
Description: Function will pop a move off of the top of the stack. If the stack is empty,
				the function will return false. 
****************************************************************************************/

bool Stack::Pop(Coordinate& moveToPop) {

	if (top != nullptr) {

		moveToPop = top->position;
		
		Node * usedMove = top;

		top = top->next;
		delete usedMove;
		usedMove = nullptr;

		return true;

	}

	return false;

}