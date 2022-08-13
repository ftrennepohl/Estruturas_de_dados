#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int * swap(int *arr, int i, int j){
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
    return arr;
}

// Merge Sort

void merge(int *arr, int start, int mid, int end)
{
    int *aux = malloc((end-start+1) * sizeof(int));
    int i = start, j = mid+1, k = 0;
    while (i<=mid && j<=end) {
        if (arr[i]<=arr[j]){
            aux[k] = arr[i];
            i++;
        }
        else {
            aux[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i<=mid){
        aux[k] = arr[i];
        k++;
        i++;
    }
    while (j<=end){
        aux[k] = arr[j];
        k++;
        j++;
    }
    for(k=start; k<=end; k++){
        arr[k] = aux[k-start];
    }
    free(aux);
    return;
}

void mergeSort(int *arr, int start, int end)
{
    if (start < end){
        int mid = (start + end) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid+1, end);
        merge(arr, start, mid, end);
    }
    return;
}

// Quick sort

int partition(int *arr, int start, int end){
    int pivot = end, k = start;
    for(int i=start; i<end; i++){
        if(arr[i] <= arr[pivot]){
            arr = swap(arr, i, k);
            k++;
        }
    }
    if (arr[k] > arr[pivot]){
        arr = swap(arr, pivot, k);
        pivot = k;
    }
    return pivot;
}

void quickSort(int *arr, int start, int end){
    int pivot;
    if (start < end){
        pivot = partition(arr, start, end);
        quickSort(arr, start, pivot-1);
        quickSort(arr, pivot+1, end);
    }
    return;
}

// Heap Sort

void heapMax(int *arr, int i, int len){
    int max = i, left = 2*i+1, right = 2*i+2;
    if (left < len && arr[left] > arr[i]) max = left;
    if (right < len && arr[right] > arr[max]) max = right;
    if (max != i){
        arr = swap(arr, i, max);
        heapMax(arr, max, len);
    }
    return;
}

void heapMin(int *arr, int i, int len){
    int min = i, left = 2*i+1, right = 2*i+2;
    if (left < len && arr[left] < arr[i]) min = left;
    if (right < len && arr[right] < arr[min]) min = right;
    if (min != i){
        arr = swap(arr, i, min);
        heapMin(arr, min, len);
    }
    return;
}

void heapSort(int *arr, int len){
    for (int i=len/2-1; i>=0; i--) heapMin(arr, i, len);
    for (int i=len-1; i>0; i--){
        swap(arr, 0, i);
        heapMin(arr, 0, i);
    }
    return;
}


// Counting Sort

void countingSort(int *arr, int len){
    int *count, maior = 0;
    for (int i=0; i<len; i++) if (arr[i] > maior) maior = arr[i];
    count = calloc(maior+1, sizeof(int));
    for (int i=0; i<len; i++) count[arr[i]]++;
    int i=0, j = 0;
    while (i<maior+1){
        if (count[i] != 0) {
            arr[j] = i;
            count[i]--;
            j++;
        } else i++;
    }
}

// Radix Sort

void radixCount(int *arr, int len, int pos){
    int *aux = malloc(len * sizeof(int));
    int *count = calloc(10, sizeof(int));
    for(int i=0; i<len; i++) count[(arr[i]/pos)%10]++;
    for(int i=1; i<10; i++) count[i] += count[i-1];
    for(int i=len-1; i>=0; i--){
        count[((arr[i]/pos)%10)]--;
        aux[count[((arr[i]/pos)%10)]] = arr[i];
    }
    for(int i=0; i<len; i++) arr[i] = aux[i];
    return;
}

void radixSort(int *arr, int len){
    int max = 0;
    for(int i=0; i<len; i++) if (arr[i] > max) max = arr[i];
    for(int pos=1; max/pos > 0; pos *= 10) radixCount(arr, len, pos);
    return;
}

// Tests

int * createarr(int *arr, int n){
	int *vet = malloc(n * sizeof(int));
	for (int i=0; i<n; i++) vet[i] = arr[i];
	return vet;
}

void msg(char *name, int end, int start){
    printf("%s Sort: %lfs\n", name, (double) (end-start)/CLOCKS_PER_SEC);
    return;
}

void tests(int *arr, int len){
    time_t start, end;
    int *testarr;
    void (*sorts[5])() = {&mergeSort, &quickSort, &heapSort, &countingSort, &radixSort};
    char names[5][9] = {"Merge", "Quick", "Heap", "Counting", "Radix"};
    for(int i=0; i<5; i++){
        testarr = createarr(arr, len);
        if (i < 2) {
            start = clock();
            (*sorts[i])(testarr, 0, len);
            end = clock();
            msg(names[i], end, start);
        } else {
            start = clock();
            (*sorts[i])(testarr, len);
            end = clock();
            msg(names[i], end, start);
        }
        free(testarr);
    }
}

int main(){
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
            arr3[j] = (rand() % (len[i]-1));
        }
        printf("====== Crescente [%dk] ======\n", len[i] / 1000);
        tests(arr1, len[i]);
        printf("\n");
        printf("====== Decrescente [%dk] ======\n", len[i] / 1000);
        tests(arr2, len[i]);
        printf("\n");
        printf("====== Aleatorio [%dk] ======\n", len[i] / 1000);
        tests(arr3, len[i]);
        printf("\n");
    }
}
	