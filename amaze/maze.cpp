/* 
maze.cpp

Author:

Short description of this file:
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main() {
   int rows, cols, result;
   char** mymaze;
   mymaze = read_maze(&rows, &cols);
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   result = maze_search(mymaze, rows, cols);

   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   // ADD CODE HERE to delete all memory 
   // that read_maze allocated
  	for(int i = 0; i < rows; i++)
  	{
  		delete [] mymaze[i];
  	}
  	delete [] mymaze;
   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) {
	//Checking if maze is valid
	bool start_is_there = false;
	bool end_is_there = false;
	Location start; 
	Location end;
	//Iterating through the maze to check if there is start and finish
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			//If there is a Start
			if(maze[r][c] == 'S')
			{
				start_is_there = true;
				//Implementing starting location 
				start.row = r; 
				start.col = c;
			}
			//IF there is an end
			if(maze[r][c] == 'F')
			{
				end_is_there = true;
				//Implenting ending location
				end.row = r;
				end.col = c;
			}
		}
	}
	//If there is not a start or an end return error (-1)
	if(!start_is_there || !end_is_there)
	{
		return -1;
	}
	
	//Creating an empty Queue 
	Queue q(rows*cols);
	//Adding the starting location to the queue
	q.add_to_back(start);
	//While the queue is not empty(there are more squares to explore)

	//Creating 2d Boolean Array to check whether a space has been explored 
	bool** explored = new bool*[rows];
	for(int i = 0; i < rows; i++)
	{
		explored[i] = new bool[cols];
	}
	//Making all the boolean values false to start
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			explored[r][c] = false;
		}
	}
	//The directions
	Location neighbors[4];
	//North
	neighbors[0].row = -1;
	neighbors[0].col = 0;
	//East
	neighbors[1].row = 0;
	neighbors[1].col = -1;
	//South
	neighbors[2].row = 1;
	neighbors[2].col = 0;
	//North
	neighbors[3].row = 0;
	neighbors[3].col = 1;

	//The start location has been explored
	explored[start.row][start.col] = true;

	//Creating a predecessors array for later use
	Location** predecessors = new Location*[rows];
	for(int i = 0; i < rows; i++)
	{
		predecessors[i] = new Location[cols];
	}


	while(!(q.is_empty()))
	{
		Location current_loc = q.remove_from_front();
		for(int i = 0; i < 4; i++)
		{
			//Creating the rows and cols to be explored next.
			int neighboring_row = current_loc.row + neighbors[i].row;
			int neighboring_col = current_loc.col + neighbors[i].col;

			//If rows are in the bounds 
			if(neighboring_row >= 0 && neighboring_row < rows) 
			{
				//If the columns are in the bounds
				if(neighboring_col >= 0 && neighboring_col < cols)
				{
					if(explored[neighboring_row][neighboring_col] == false)
					{
						//If the space is empty 
						if(maze[neighboring_row][neighboring_col] == '.')
						{
							//Add the unexplored location to the queue
							Location newLocation;
							newLocation.row = neighboring_row;
							newLocation.col = neighboring_col;
							q.add_to_back(newLocation);
							//Declare the space has been explored
							explored[neighboring_row][neighboring_col] = true;
							//What Location led me to get to this new one.
							predecessors[neighboring_row][neighboring_col]
							 	= current_loc;
						}
						else if(maze[neighboring_row][neighboring_col] == 'F')
						{
							predecessors[neighboring_row][neighboring_col] 
									= current_loc;
							end.row = neighboring_row;
							end.col = neighboring_col;
							//Finish line has been explored!
							explored[neighboring_row][neighboring_col] = true;
						}
					}
				}
			}
		}
	}

		
	//Location starting at the finish and going backwards
	if(explored[end.row][end.col] == false)
	{
		for(int i = 0; i < rows; i++)
		{
			delete[] predecessors[i];
		}
		delete [] predecessors;

		for(int i = 0; i < rows; i++)
		{
			delete[] explored[i];
		}
		delete [] explored;
		return 0;
	}

	//Tracing back to find path
	//While we haven't reached the start yet.
	end = predecessors[end.row][end.col];
	while(end.row != start.row || end.col != start.col)
	{
		maze[end.row][end.col] = '*';
		end = predecessors[end.row][end.col];
	}

	for(int i = 0; i < rows; i++)
	{
		delete[] predecessors[i];
	}
	delete [] predecessors;

	for(int i = 0; i < rows; i++)
	{
		delete[] explored[i];
	}
	delete [] explored;

	return 1;
}
