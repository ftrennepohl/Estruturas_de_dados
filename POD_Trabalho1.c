#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct data
{
	long int comps, swaps;
} Data;

void initData(Data **res){
	for (int i=0; i<3; i++){
		res[i]->comps = 0;
		res[i]->swaps = 0;
	}
}

Data bubbleSort(int *vet, int n, Data res)
{
	int flag;
	for (int i = n - 1; i > 0; i--){
		flag = 0;
		for (int j = 0; j < i; j++){
			res.comps++;
			if (vet[j] > vet[j + 1]){
				int aux = vet[j + 1];
				vet[j + 1] = vet[j];
				vet[j] = aux;
				res.swaps++;
				flag = 1;
			}
		}
		if (!flag){
			return res;
		}
	}
	return res;
}

Data selectionSort(int *vet, int n, Data res)
{
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

Data insertionSort(int *vet, int n, Data res){
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

int * CriaVet(int *arr, int n){
	int *vet = malloc(n * sizeof(int));
	for (int i=0; i<n; i++) vet[i] = arr[i];
	return vet;
}

void testes(int *arr, int n)
{
	time_t start, end;
	Data res1, res2, res3;
	Data *res[3] = {&res1, &res2, &res3};
	initData(res);
	int *vet1, *vet2, *vet3;
	vet1 = CriaVet(arr, n);
	vet2 = CriaVet(arr, n);
	vet3 = CriaVet(arr, n);
	start = clock();
	res1 = bubbleSort(vet1, n, res1);
	end = clock();
	printf("Bubble: %.3lfs Comparacoes: %ld, Trocas: %ld\n", (double)(end - start) / CLOCKS_PER_SEC, res1.comps, res1.swaps);
	start = clock();
	res2 = selectionSort(vet2, n, res2);
	end = clock();
	printf("Selection: %.3lfs Comparacoes: %ld, Trocas: %ld\n", (double)(end - start) / CLOCKS_PER_SEC, res2.comps, res2.swaps);
	start = clock();
	res3 = insertionSort(vet3, n, res3);
	end = clock();
	printf("Insertion: %.3lfs Comparacoes: %ld, Trocas: %ld\n", (double)(end - start) / CLOCKS_PER_SEC, res3.comps, res3.swaps);
	free(vet1);
	free(vet2);
	free(vet3);
	return;
}

void testarSort()
{
	int *vet = malloc(100 * sizeof(int));
	Data res;
	srand(time(NULL));
	printf("============== Nao ordenados ==============\n");
	for (int i=0; i<100; i++) {
		vet[i] = (rand() % (99 - 1)) + 1;
		printf("%d\n", vet[i]);
	}
	res = bubbleSort(vet, 100, res);
	printf("============== Ordenados ==============\n");
	for (int i=0; i<100; i++) printf("%d\n", vet[i]);
	return;
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
			arr3[j] = (rand() % 99) + 1;
		}
		printf("====== Crescente [%dk] ======\n", len[i] / 1000);
		testes(arr1, len[i]);
		printf("\n");
		printf("====== Decrescente [%dk] ======\n", len[i] / 1000);
		testes(arr2, len[i]);
		printf("\n");
		printf("====== Aleatorio [%dk] ======\n", len[i] / 1000);
		testes(arr3, len[i]);
		printf("\n");
	}
	return 0;
}
