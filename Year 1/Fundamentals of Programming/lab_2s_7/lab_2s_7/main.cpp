#include "graph.h"

#include <fstream>
#include <iostream>

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int idx = low - 1;

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] < pivot)
		{
			idx++; 
			swap(&arr[idx], &arr[j]);
		}
	}
	swap(&arr[idx+1], &arr[high]);
	return idx + 1;
}

void quick_sort(int arr[], int low, int high)
{
	if (low < high)
	{
		int part = partition(arr, low, high);

		quick_sort(arr, low, part - 1);
		quick_sort(arr, part + 1, high);
	}
}



int main()
{

	char name[] = "graph.txt";
	//int arr[] = { 10, 80, 30, 90, 40, 50, 70 };

	grp::LineList list = grp::read(name);
	//list.printList();

	list.quicksort(list.head, list.tail);
	list.printList();

	return 0;
}