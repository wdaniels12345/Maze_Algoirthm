//Walker Daniels
//Intro to Artificial Intelligence
//9/24/22
//This program implements a search algorithm into a maz that is read from a text file
#include <stdio.h>
#include <stdlib.h>

char** maze; // this is our actual maze the one that we read our file into
int** maze2; // this is a tester maze for simplicity reasons, it helps for me to visualize the maze in the .c file as well
int rows, cols, startRow, startCol;


enum terrain
{  //defines an enumeration that is the effectively the boundaries of the maze
	empty,
	wall,
	goal,
	trail
};

void allocMaze() // here I allocate memory for maze 1
{
	maze = malloc(rows * sizeof(char*));
	for (int i = 0; i < rows; ++i){
		maze[i] = malloc(cols * sizeof(char*));
	}
}


void allocMaze2() // here I allocate memory for maze 2
{
	maze2 = malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; ++i){
		maze2[i] = malloc(cols * sizeof(int*));
	}
}

void getMaze(char* file_name) // this is where I get and set my maze
{
	char c;
	char rows_s[5] = { '\0' };
	char cols_s[5] = { '\0' };
	int rows_i = 0;
	int cols_i = 0;
	int swap = 0;

	FILE* mazeFile = fopen(file_name, "r"); // here I read my file

	if (mazeFile)
	{
		while ((c = getc(mazeFile)) != EOF)
		{
			if (c == '\n')
			{
				break;
			} else if (c == ',')
			{
				swap = 1;
			} else if (!swap)
			{
				rows_s[rows_i] = c;
				rows_i++;
			} else
			{
				cols_s[cols_i] = c;
				cols_i++;
			}
		}
	} else
	{
		printf("No such file!");
		return;
	}

	rows = atoi(rows_s);
	cols = atoi(cols_s);

	allocMaze();


	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{

			if ((c = getc(mazeFile)) == '\n')
			{
				c = getc(mazeFile);
			}

			maze[i][j] = c;

			if (c =='s')
			{
				startRow = i;
				startCol = j;
			}
		}
	}

	fclose(mazeFile);
}

//Finally the maze should be read into my maze array

void initMaze2()
{
	allocMaze2();

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (maze[i][j] == '+')
			{
				maze2[i][j] = wall;
			} else if (maze[i][j] == 's')
			{
				maze2[i][j] = goal;
			} else
			{
				maze2[i][j] = empty;
			}
		}
	}
}

void printMaze() //here my maze is displayed
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void add()
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (maze[i][j] != 's' && maze2[i][j] == trail)
			{
				maze[i][j] = '.';
			}
		}
	}
}

int mathMaze(int row, int col) // this is the main part of the entire build.. These if statements are the algorithm used to track and backtrack through maze path
{
	int* test = &maze2[row][col];

	if (*test == goal)
	{
		return 1;
	}

	if (*test == empty)
	{
		*test = trail;

		if (mathMaze(row+1, col))
		{
			*test = trail;
			return 1;
		}
		if (mathMaze(row, col+1))
		{
			*test = trail;
			return 1;
		}
		if (mathMaze(row-1, col))
		{
			*test = trail;
			return 1;
		}
		if (mathMaze(row, col-1))
		{
			*test = trail;
			return 1;
		}
	}

	return 0;
}

int main()
{
	getMaze("maze.txt");
	initMaze2();

	printMaze();

	if (!mathMaze(startRow, startCol))
	 {
		printf("No path found \n");
	} else
	{
		add();
		printMaze();
	}
	return 0;
}
