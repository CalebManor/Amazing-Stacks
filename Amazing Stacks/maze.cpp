/****************************************************************************************
Name: maze.cpp
Description: This file is used to solve mazes by using the stack ADT. The file input
				vital information from an input file. This information will include
				the dimensions of the mazes, starting locations, and exits of each maze.
				Upon each maze completion, the application will output each maze and
				will state whether or not an exit exists in each maze. 
Author: Caleb Manor
****************************************************************************************/

#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

/****************************************************************************************
FUNCTION PROTOTYPES
****************************************************************************************/

void MazeInsertion(int, int, char[][80], int, int, ifstream&);
void PrintMaze(int, int, char[][80], ofstream&);
bool MazeSolver(int, int, int, char[][80], int, int, ofstream&);

/****************************************************************************************
Function: Main
Description: Function will initialize constants, variables, and input and output files. 
				The main function will use each of these components to make calls to 
				functions that will insert the maze into the 2-D character array maze 
				and will subsequently search for a solution to each maze using the 
				maze solver function. 
****************************************************************************************/

void main() {

	const int PUZZLE_LIMIT = 80;
	const int EMPTY = 0;

	int rowSize = EMPTY;
	int columnSize = EMPTY;

	int startingRow = EMPTY;
	int startingColumn = EMPTY;

	int mazeCount = 1;

	char maze[PUZZLE_LIMIT][PUZZLE_LIMIT];

	ifstream fin("Maze.txt");
	ofstream fout;
	fout.open("mazeSolutions.txt");

	while (rowSize != -1 && columnSize != -1) {

		fin >> rowSize >> columnSize;

		if (rowSize != -1 && columnSize != -1) {

			fout << "MAZE NUMBER " << mazeCount << endl << endl;
			mazeCount++;
			
			MazeInsertion(rowSize, columnSize, maze, startingRow, startingColumn, fin);
			fin >> startingRow >> startingColumn;
			MazeSolver(mazeCount, startingRow, startingColumn, maze, rowSize, columnSize, fout);

		}

	}

	fin.close();
	fout.close();

}

/****************************************************************************************
Function: MazeInsertion
Description: Function will insert a maze into the 2-D character array maze
****************************************************************************************/

void MazeInsertion(int rowSize, int columnSize, char maze[][80]
	, int startingRow, int startingColumn, ifstream& fin) {

	for (int rowIndex = 0; rowIndex < rowSize; rowIndex++) {
		for (int columnIndex = 0; columnIndex < columnSize; columnIndex++) {
			fin >> maze[rowIndex][columnIndex];
		}
	}

}

/****************************************************************************************
Function: PrintMaze
Description: Function will print each maze to the output file mazeSolutions.txt
****************************************************************************************/

void PrintMaze (int rowSize, int columnSize, char maze[][80], ofstream& fout) {

	for (int rowIndex = 0; rowIndex < rowSize; rowIndex++) {
		for (int columnIndex = 0; columnIndex < columnSize; columnIndex++) {
			fout << maze[rowIndex][columnIndex];
		}
		fout << endl;
	}

}

/****************************************************************************************
Function: MazeSolver
Description: Function is used to solve each maze by interacting with the stack ADT. By
				using the maze inserted into the 2-D array, the function will first
				initialize a starting position and adjacent cardinal coordinates. The 
				function will repeatedly check each positions in each maze and will
				push possible next moves onto the stack. After checking to see if a move
				is the exit, the function will drop a "breadcrumb" signifiying that the
				position was visited and thereby preventing it being pushed back onto 
				the stack. If an exit is found or not, such information will be printed
				to the output file. 
****************************************************************************************/

bool MazeSolver(int mazeCount, int startingRow, int startingColumn, char maze[][80]
	, int rowSize, int columnSize, ofstream& fout) {

	Stack MovesList;

	Coordinate currentPosition;
	currentPosition.Row = startingRow;
	currentPosition.Column = startingColumn;

	Coordinate North;
	North.Row = currentPosition.Row - 1;
	North.Column = currentPosition.Column;

	Coordinate East;
	East.Row = currentPosition.Row;
	East.Column = currentPosition.Column + 1;

	Coordinate South;
	South.Row = currentPosition.Row + 1;
	South.Column = currentPosition.Column;

	Coordinate West;
	West.Row = currentPosition.Row;
	West.Column = currentPosition.Column - 1;

	bool exitLoop = false;

	do {

		if (maze[currentPosition.Row][currentPosition.Column] == 'E') {

			PrintMaze(rowSize, columnSize, maze, fout);
			fout << endl;
			fout << "There IS a way out!";
			fout << endl << endl;
			return true;

		}

		/********************************************************************************
		Pushes all usable moves onto the MovesList stack
		********************************************************************************/

		if (maze[currentPosition.Row][currentPosition.Column] == '0') {

			if (maze[North.Row][North.Column] == '0' || maze[North.Row][North.Column] == 'E')
				MovesList.Push(North);

			if (maze[East.Row][East.Column] == '0' || maze[East.Row][East.Column] == 'E')
				MovesList.Push(East);

			if (maze[South.Row][South.Column] == '0' || maze[South.Row][South.Column] == 'E')
				MovesList.Push(South);

			if (maze[West.Row][West.Column] == '0' || maze[West.Row][West.Column] == 'E')
				MovesList.Push(West);

		}

		maze[currentPosition.Row][currentPosition.Column] = '.';

		/********************************************************************************
		Initializes a new current position and cardinal moves from a move that was 
		popped off of the stack. 
		********************************************************************************/

		MovesList.Pop(currentPosition);

		North.Row = currentPosition.Row - 1;
		North.Column = currentPosition.Column;

		East.Row = currentPosition.Row;
		East.Column = currentPosition.Column + 1;

		South.Row = currentPosition.Row + 1;
		South.Column = currentPosition.Column;

		West.Row = currentPosition.Row;
		West.Column = currentPosition.Column - 1;

		/********************************************************************************
		If the list is empty and all nearby moves are unusable, there is no way out
		********************************************************************************/

		if ((MovesList.Empty() == true)) {
			if (maze[North.Row][North.Column] != '0' && maze[North.Row][North.Column] != 'E') {
				if (maze[East.Row][East.Column] != '0' && maze[East.Row][East.Column] != 'E') {
					if (maze[South.Row][South.Column] != '0' && maze[South.Row][South.Column] != 'E') {
						if (maze[West.Row][West.Column] != '0' && maze[West.Row][West.Column] != 'E') {
							exitLoop = true;
						}
					}
				}
			}
		}

	} while (exitLoop == false);

	PrintMaze(rowSize, columnSize, maze, fout);
	fout << endl;
	fout << "There is NOT a way out!";
	fout << endl << endl;
	return false;

}