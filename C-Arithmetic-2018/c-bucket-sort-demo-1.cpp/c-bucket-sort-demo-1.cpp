// c-bucket-sort-demo-1.cpp
#include <iostream>
#include <stdio.h>
#include <malloc.h>
// #include <time.h>

using namespace std;

void PA_DisplayData(int data[], int nCount){
    for(int i = 0; i < nCount; i++){
        if(i) printf(", ");
        printf("%d", data[i]);
    }
    printf("\n");
}


const int MAX = 100;
const int bn = 5;

const int nFactor = MAX % bn ? MAX / bn + 1 : MAX / bn;

int C[bn];

void InsertionSort(int A[], int left, int right){
    for(int i = left + 1; i <= right; i++){
        int get = A[i];
        int j = i - 1;
        while(j >= left && A[j] > get){
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = get;
    }
}

int MapToBucket(int x){
    return x / nFactor;
}

void CountingSort(int A[], int n){
    for(int i = 0; i < bn; i++){
        C[i] = 0;
    }
    for(int i = 0; i < n; i++){
        C[MapToBucket(A[i])]++;
    }
    for(int i = 1; i < bn; i++){
        C[i] = C[i] + C[i - 1];
    }
    int * B = (int *)malloc(n * sizeof(int));
    for(int i = n - 1; i >= 0; i--){
        int b = MapToBucket(A[i]);
        B[--C[b]] = A[i];
    }
    for(int i = 0; i < n; i++){
        A[i] = B[i];
    }
    free(B);
}

void BucketSort(int A[], int n){
    CountingSort(A, n);
    for(int i = 0; i < bn; i++){
        int left = C[i];
        int right = (i == bn - 1 ? n - 1 : C[i + 1] - 1); // C[i + 1] - 1为i号桶最后一个元素的位置
        if(left < right){
            InsertionSort(A, left, right);
        }
    }
}

int main(){
    // int _source[] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36};
    int _source[] = {76, 11, 11, 43, 78, 35, 39, 27, 16, 55, 1, 41, 24, 19, 54, 7, 78, 69, 65, 82};
    int nCount = sizeof(_source) / sizeof(int);

    printf("Item count: %d\n", nCount);

    // srand(time(NULL));
    // for(int i = 0; i < 20; i++){
    //     _source[i] = rand() % 1000;
    // }

    PA_DisplayData(_source, nCount);
    BucketSort(_source, nCount);
    PA_DisplayData(_source, nCount);
    
    return 0;
}