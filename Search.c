#include <stdio.h>

// Complexity: O(n)
int searchUnsortedArray(int *arr, int size, int targ)
{
    for(int i = 0; i <= size; i++){
        if (arr[i] == targ) return targ;
    }
    return -1;
}

int searchSortedArray(int *arr, int size, int targ)
{
    int first = 0, last = size, mid = (last + first) / 2;

    while (first <= last){
        if (targ == arr[mid]) break;
        if (targ > arr[mid]) first = mid+1;
        else last = mid-1;
        mid = (last + first) / 2;
    }
    if (first > last) return -1;
    else return arr[mid];
}

int searchSortedArrayRecursive(int *arr, int first, int last, int targ)
{   
    if (first > last) return -1;
    int mid = (last + first) / 2;
    if (targ == mid) return targ;

    if (targ < arr[mid]) return searchSortedArrayRecursive(arr, first, mid-1, targ);
    else return searchSortedArrayRecursive(arr, mid+1, last, targ);
}

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("%d\n", searchUnsortedArray(arr, 9, 11));
    printf("%d\n", searchSortedArray(arr, 9, 6));
    printf("%d\n", searchSortedArrayRecursive(arr, 0, 9, 3));
    return 0;
}