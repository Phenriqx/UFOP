#include "sort.h"

int main() {
	int arr[] = {4, 1, 5, 9, 10, 3, 2, 0, 7};
	printArray(arr, 9);

	//bubbleSort(arr, 9);
	//selectionSort(arr, 9);	
	insertionSort(arr, 9);
	
	printArray(arr, 9);

	return 0;
}
