#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int *vet, int n)
{
	for (int i = n - 1; i > 0; i--)
		for (int j = 0; j < i; j++){
			if (vet[j] > vet[j + 1])
			{
				int aux = vet[j + 1];
				vet[j + 1] = vet[j];
				vet[j] = aux;
			}
		}
}

void selectionSort(int *vet, int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = i; j < n; j++)
			if (vet[j] < vet[i])
			{
				int aux = vet[j];
				vet[j] = vet[i];
				vet[i] = aux;
			}
	for (int j = 0; j < n; j++)
		printf("%d ", vet[j]);
}

void insertionSort(int *vet, int n)
{
	for (int i = 1; i < n; i++) {
		int key = vet[i];
		int j = i-1;
		while (vet[j] > key && j >=0){
			int aux = vet[j+1];
			vet[j+1] = vet[j];
			vet[j] = aux; 
			j--;
		}
	}
	for (int j = 0; j < n; j++)
		printf("%d ", vet[j]);
}

void countingSort(int *arr, int len){
	int *aux, max = 0;
	for (int i=0; i<len; i++) if (arr[i] > max) max = arr[i];
	aux = calloc(max+1, sizeof(int));
	for (int i=0; i<len; i++) aux[arr[i]]++;
	int i=0, j=0;
	while(i <= max){
		if (aux[i]!=0){
			arr[j] = i;
			aux[i]--;
			j++;
		} else i++;
	}
}

void testarSort()
{
	int len = 100;
	int *arr;
	arr = malloc(len * sizeof(int));
	srand(time(NULL));
	for (int i=0; i<len; i++) arr[i] = rand() % len;
	countingSort(arr, len);
	for (int i=0; i<len; i++) printf("%d\n", arr[i]);
}

int main()
{
	testarSort();
}