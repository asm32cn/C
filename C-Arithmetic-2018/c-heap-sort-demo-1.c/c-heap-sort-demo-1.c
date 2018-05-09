// c-heap-sort-demo-1.c
#include <stdio.h>

void PA_DisplayData(int data[], int nCount){
    for(int i = 0; i < nCount; i++){
        if(i) printf(", ");
        printf("%d", data[i]);
    }
    printf("\n");
}

void Swap(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void Heapify(int A[], int i, int size){
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;
    int max = i;
    if(left_child < size && A[left_child] > A[max]){
        max = left_child;
    }
    if(right_child < size && A[right_child] > A[max]){
        max = right_child;
    }
    if(max != i){
        Swap(A, i, max);
        Heapify(A, max, size);
    }
}

int BuildHeap(int A[], int n){
    int heap_size = n;
    for(int i = heap_size / 2 - 1; i >= 0; i--){
        Heapify(A, i, heap_size);
    }
    return heap_size;
}

void HeapSort(int A[], int n){
    int heap_size = BuildHeap(A, n);
    while(heap_size > 1){
        Swap(A, 0, --heap_size);
        Heapify(A, 0, heap_size);
    }
}

void main(){
    // int _source[] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36};
    int _source[] = {76, 11, 11, 43, 78, 35, 39, 27, 16, 55, 1, 41, 24, 19, 54, 7, 78, 69, 65, 82};
    int nCount = sizeof(_source) / sizeof(int);

    printf("Item count: %d\n", nCount);

    // srand(time(NULL));
    // for(int i = 0; i < 20; i++){
    //     _source[i] = rand() % 100;
    // }

    PA_DisplayData(_source, nCount);
    HeapSort(_source, nCount);
    PA_DisplayData(_source, nCount);
}