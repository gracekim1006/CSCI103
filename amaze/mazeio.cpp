/* 
mazeio.cpp

Author:

Short description of this file:
*/

#include <iostream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from cin into a dynamically allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * such as integers for the size not found.
 *
 * We also pass in two pointers to integers. Fill 
 * the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(int* rows, int* cols) {
   // FILL THIS IN
	cin >> *rows;
	cin >> *cols;

	//Creating the space for the maze;
	char** maze = new char*[*rows];
	for(int i = 0; i < *rows; i++)
	{
		maze[i] = new char[*cols];
	}
	//USing cin to fill in the maze
	for(int r = 0; r < *rows; r++)
	{
		for(int c = 0; c < *cols; c++)
		{
			cin >> maze[r][c]; 
		}
	}
	return maze;

}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) {
   // FILL THIS IN
	cout << rows << " ";
	cout << cols << endl;
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			cout << maze[r][c]; 
		}
		cout << endl;
	}
}

