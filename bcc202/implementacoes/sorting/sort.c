#include <stdio.h>
#include <stdbool.h>

#include "sort.h"

void bubbleSort(int arr[], int n) {
	int troca;
	for (int i = 0; i < n - 1; i++) {
		troca = false;
		for (int j = 0; j < n - 1 - i; j++)
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				troca = true;
			}
		if (troca == false)
			break;
	}
}

void selectionSort(int *arr, int n) {
	int min;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[min])
				min = j;
		}
		if (i != min) {
			int temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}

void insertionSort(int *arr, int n) {
	int aux, j;
	for (int i = 1; i < n; i++) {
		aux = arr[i];
		j = i - 1;
		while (j >= 0 && aux < arr[j]) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = aux;
	}
}

void mergeRec(int *arr, int l, int r);
void merge(int *arr, int l, int m, int r);

void mergeSort(int *arr, int n) {
	mergeRec(arr, 0, n - 1);	
}

void mergeRec(int *arr, int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		mergeRec(arr, l, m);
		mergeRec(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

void merge(int *arr, int l, int m, int r) {
	
}

void printArray(int arr[], int n) {
	for (int i = 0; i < n; i++) 
		printf("%d ", arr[i]);
	printf("\n");
}
