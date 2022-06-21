#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct data
{
	int comps, swaps;
} Data;

Data bubbleSort(int *arr, int n)
{
	int *vet = arr;
	int flag;
	Data res;
	res.comps = 0;
	res.swaps = 0;
	for (int i = n - 1; i > 0; i--)
	{
		flag = 0;
		for (int j = 0; j < i; j++)
		{
			res.comps++;
			if (vet[j] > vet[j + 1])
			{
				int aux = vet[j + 1];
				vet[j + 1] = vet[j];
				vet[j] = aux;
				res.swaps++;
				flag = 1;
			}
		}
		if (!flag)
		{
			return res;
		}
	}
	return res;
}

Data selectionSort(int *arr, int n)
{
	int *vet = malloc(n * sizeof(int));
	vet = arr;
	Data res;
	res.comps = 0;
	res.swaps = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i; j < n; j++)
		{
			res.comps++;
			if (vet[j] < vet[i])
			{
				int aux = vet[j];
				vet[j] = vet[i];
				vet[i] = aux;
				res.swaps++;
			}
		}
	return res;
}

Data insertionSort(int *arr, int n)
{
	int *vet = arr;
	Data res;
	res.comps = 0;
	res.swaps = 0;
	for (int i = 1; i < n; i++){
		int key = vet[i];
		int j = i - 1;
		res.comps++;
		while (vet[j] > key && j >= 0){
			int aux = vet[j + 1];
			vet[j + 1] = vet[j];
			vet[j] = aux;
			j--;
			res.swaps++;
		}
	}
	return res;
}

void testes(int *arr, int len)
{
	Data res;
	clock_t begin, end;

	begin = time(NULL);
	res = bubbleSort(arr, len);
	end = time(NULL);
	printf("bubble: %.2lfs res0: %d, res1: %d\n", (double)(end - begin), res.comps, res.swaps);
	begin = time(NULL);
	res = selectionSort(arr, len);
	end = time(NULL);
	printf("selection: %.2lfs\n", (double)(end - begin));
	begin = time(NULL);
	res = insertionSort(arr, len);
	end = time(NULL);
	printf("insertion: %.2lfs\n", (double)(end - begin));
}

int main()
{
	int *arr1, *arr2, *arr3;
	int len[3] = {10000, 50000, 100000};
	for (int i = 0; i < 3; i++){
		arr1 = malloc(len[i] * sizeof(int));
		arr2 = malloc(len[i] * sizeof(int));
		arr3 = malloc(len[i] * sizeof(int));
		srand(time(NULL));
		int k = len[i];
		for (int j = 0; j < len[i]; j++){
			arr1[j] = j;
			arr2[j] = k;
			k--;
			arr3[j] = (rand() % (99 - 1)) + 1;
		}
		printf("====== Crescente [%dk] ======\n", len[i] / 1000);
		testes(arr1, len[i]);
		printf("====== Decrescente [%dk] ======\n", len[i] / 1000);
		testes(arr2, len[i]);
		printf("====== Aleatorio [%dk] ======\n", len[i] / 1000);
		testes(arr3, len[i]);
	}
	return 0;
}
