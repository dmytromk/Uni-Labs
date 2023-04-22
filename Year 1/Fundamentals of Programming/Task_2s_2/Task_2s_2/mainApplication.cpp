#include <iostream>
#include "Labyrinth.h"

bool borders(int row, int col, int ROW, int COL)
{
	return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

/*template <size_t row, size_t col>
void printMatrix(int matrix[row][col])
{
	for (int i = 0; i < row; i++)
	{
		for (int k = 0; k < col; k++)
		{
			std::cout << matrix[i][k] << " ";
		}
		std::cout << "\n";
	}
}
*/



template <size_t row, size_t col>
void printRoute(labyrinth::LabyrStack list, int start_x, int start_y,
	int end_x, int end_y, int (&matrix)[row][col])
{
	const int ROWS[] = { -1, 0, 0, 1 };
	const int COLS[] = { 0, -1, 1, 0 };

	if (matrix[end_y][end_x] != 1)
	{
		std::cout << "Incorrect end point info.\n";
		return;
	}

	labyrinth::Point* current = new labyrinth::Point(start_x, start_y);
	int cur_x = start_x;
	int cur_y = start_y;
	list.add(current);

	/*bool visited[ROW][COL];
	memset(visited, false, sizeof visited);

	int d = 5;
	matrix[start_y][start_x] = d;
	visited[start_y][start_x] = true;*/

	matrix[start_y][start_x] = 2;

	while (cur_x != end_x || cur_y != end_y)
	{
		int i = 0;
		for (i; i < 4; i++)
		{
			int temp_row = cur_y + ROWS[i];
			int temp_col = cur_x + COLS[i];
			if (borders(cur_y + ROWS[i], cur_x + COLS[i], row, col))
			{
				if (matrix[temp_row][temp_col] == 1)
				{
					matrix[temp_row][temp_col] = 2;
					labyrinth::Point* temmp = new labyrinth::Point(temp_col, temp_row);
					list.add(temmp);
					cur_x = temp_col;
					cur_y = temp_row;
					break;
				};
			};
		};

		if (i == 4)
		{
			list.delLast();
			if (!list.head)
			{
				std::cout << "No way!\n";
				return;
			}
			cur_x = list.tail->info->x;
			cur_y = list.tail->info->y;
		};

	};


	list.printStack();
	
}

int main()
{

	int a[5][5] =
	{
		0, 1, 1, 1, 0,
		0, 0, 0, 0, 0,
		1, 1, 1, 0, 0,
		0, 0, 1, 0, 1,
		0, 0, 1, 1, 1
	}; 
	labyrinth::LabyrStack list;


	printRoute(list, 0, 2, 4, 3, a);
}