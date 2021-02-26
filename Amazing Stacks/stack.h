/****************************************************************************************
Name: stack.h
Description: This file contains the function prototypes for the stack ADT. The ADT will 
				work alongside maze.cpp, an application written to utilize the stack in
				order to solve mazes. 
Author: Caleb Manor
****************************************************************************************/

/****************************************************************************************
Creates a structure that will hold the coordinates of a point inside of the maze
****************************************************************************************/

struct Coordinate {
	int Row;
	int Column;
};

/****************************************************************************************
Creates a node structure to be used in the moves stack for the maze solver
****************************************************************************************/

struct Node {
	Coordinate position;
	Node * next;
};

/****************************************************************************************
Stack Function Prototypes
****************************************************************************************/

class Stack {
public:
	Stack();
	~Stack();
	bool Empty();
	bool Push(Coordinate);
	bool Pop(Coordinate&);
private:
	Node * top;
};
