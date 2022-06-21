#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *vet, int n);
void selectionSort(int *vet, int n);
void insertionSort(int *vet, int n);

int main()
{
	// int n;
	// scanf("%d", &n);
	int vet[9] = {7, 10, 5, 3, 8, 4, 2, 9, 6};
	// for (int i = 0; i < n; i++)
	//	scanf("%d", &vet[i]);
	insertionSort(vet, 9);
}

void bubbleSort(int *vet, int n)
{
	for (int i = n - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
		{
			if (vet[j] > vet[j + 1])
			{
				int aux = vet[j + 1];
				vet[j + 1] = vet[j];
				vet[j] = aux;
			}
		}
	for (int j = 0; j < n; j++)
		printf("%d ", vet[j]);
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


