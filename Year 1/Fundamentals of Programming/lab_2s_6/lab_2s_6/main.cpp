#include <fstream>
#include <iostream>

int** read(char* NAME)
{
	std::ifstream file(NAME, std::ifstream::in);

	int size;
	file >> size;

	int** matrix = new int* [size];

	for (int i = 0; i < size; i++)
	{
		//fill matrix with zeroes
		matrix[i] = new int[size];
		memset(matrix[i], 0, size * sizeof(int));
	}

	int a, b;
	while (file >> a >> b)
	{
		matrix[b - 1][a - 1] = 1;
		matrix[a - 1][b - 1] = 1;
	}

	file.close();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			std::cout << matrix[i][j] << " ";
		std::cout << "\n";
	}

	std::cout << "\n\n";

	return matrix;
}

void minor(int row, int col, int size, int** mtrx, int** result)
{
	//i-row, j-col
	for (int j = 0; j < size; j++)
	{
		//iterate through rows

		for (int i = 0; i < size; i++)
		{
			//iterate through columns

			if (i != col && j != row)
			{
				int temp_i = i;
				int temp_j = j;
				if (temp_i > col) temp_i--;
				if (temp_j > row) temp_j--;
				result[temp_j][temp_i] = mtrx[j][i];
			}
		}
	}
}

void del(int** mtrx, int size)
{
	for (int i = 0; i < size; i++) {
		delete[] mtrx[i];
	}
	delete[] mtrx;
}

int det(int** mtrx, int size)
{
	if (size == 1 || size == 0)
		return 0;

	else if (size == 2)
		return mtrx[0][0] * mtrx[1][1] - 
		mtrx[0][1] * mtrx[1][0];

	else
	{
		int sign = 1;
		int result = 0;
		for (int i = 0; i < size; i++)
		{

			int** min = new int*[size-1];
			for (int i = 0; i < size-1; i++)
			{
				min[i] = new int[size - 1];
				memset(min[i], 0, (size - 1) * sizeof(int));
			}
			minor(i, 0, size, mtrx, min);

			result += mtrx[i][0] * sign * det(min, (size - 1));
			del(min, size - 1);
			sign *= (-1);
		}
		return result;
	}
}


int main()
{
	char name[] = "graph.txt";
	std::ifstream file(name, std::ifstream::in);

	int size;
	file >> size;

	file.close();

	int** matrix = read(name);

	//int** matrix2 = new int* [size -1];
	//for (int i = 0; i < size - 1; i++)
	//{
	//	matrix2[i] = new int[size - 1];
	//	memset(matrix2[i], 0, (size - 1) * sizeof(int));
	//}
	//minor(2, 1, size, matrix, matrix2);

	//for (int i = 0; i < size - 1; i++)
	//{
	//	for (int j = 0; j < size-1; j++)
	//		std::cout << matrix2[i][j] << " ";
	//	std::cout << "\n";
	//}
	//std::cout << "\n\n";

	std::cout << det(matrix, size);
}