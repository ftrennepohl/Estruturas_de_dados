#include <stdio.h>
#include <stdlib.h>

// Bubble sort
int * genArr(int n){
    int *arr = malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i=0; i<n; i++) {
        arr[i] = rand() % 9999;
    }
    return arr;
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

// Selection Sort

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

// Insertion Sort

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

// Merge Sort

void merge(int *v, int start, int mid, int end)
{
    int *aux = malloc((end-start+1) * sizeof(int));
    int i = start, j = mid+1, k = 0;
    while (i<=mid && j<=end) {
        if (v[i]<=v[j]){
            aux[k] = v[i];
            i++;
        }
        else {
            aux[k] = v[j];
            j++;
        }
        k++;
    }
    while (i<=mid){
        aux[k] = v[i];
        k++;
        i++;
    }
    while (j<=end){
        aux[k] = v[j];
        k++;
        j++;
    }
    for(k=start; k<=end; k++){
        v[k] = aux[k-start];
    }
    free(aux);
}

void mergeSort(int *v, int start, int end)
{
    if (start < end){
        int mid = (start + end) / 2;
        mergeSort(v, start, mid);
        mergeSort(v, mid+1, end);
        merge(v, start, mid, end);
    }
}

// Heap Sort

int * heapMax(int *v, int n){
    for (int i=n; i > 0 ; i--) {
        int j = i;
        while (j > 0 && v[(j-1)/2] < v[j]){
            int aux = v[j];
            v[j] = v[(j-1)/2];
            v[(j-1)/2] = aux;
            j = (j-1)/2;
        }
    }
    return v;
}

// Counting Sort

void countingSort(){
    int *arr, *count, n, maior = 0;
    scanf("%d", &n);
    arr = genArr(n);
    for (int i=0; i<n; i++) if (arr[i] > maior) maior = arr[i];
    count = calloc(maior+1, sizeof(int));
    for (int i=0; i<n; i++) count[arr[i]]++;
    int i=0, j = 0;
    while (i<maior+2){
        if (count[i] != 0) {
            arr[j] = i;
            count[i]--;
            j++;
        } else i++;
    }
}

// Radix Sort

int main()
{
	// int n;
	// scanf("%d", &n);
	int vet[9] = {7, 10, 5, 3, 8, 4, 2, 9, 6};
	// for (int i = 0; i < n; i++)
	//	scanf("%d", &vet[i]);
	insertionSort(vet, 9);
}