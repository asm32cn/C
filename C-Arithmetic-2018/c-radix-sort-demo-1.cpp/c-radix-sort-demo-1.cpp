// c-radix-sort-demo-1.cpp
#include <iostream>
#include <stdio.h>
#include <malloc.h>

using namespace std;

void PA_DisplayData(int data[], int nCount){
    for(int i = 0; i < nCount; i++){
        if(i) printf(", ");
        printf("%d", data[i]);
    }
    printf("\n");
}



const int dn = 3;
const int k = 10;
int C[k];

int GetDigit(int x, int d){
    int radix[] = {1, 1, 10, 100};
    return (x / radix[d]) % 10;
}

void CountingSort(int A[], int n, int d){
    for(int i = 0; i < k; i++){
        C[i] = 0;
    }
    for(int i = 0; i < n; i++){
        C[GetDigit(A[i], d)]++;
    }
    for(int i = 1; i < k; i++){
        C[i] = C[i] + C[i - 1];
    }
    int *B = (int *)malloc(n * sizeof(int));
    for(int i = n - 1; i >= 0; i--){
        int dight = GetDigit(A[i], d);
        B[--C[dight]] = A[i];
    }
    for(int i = 0; i < n; i++){
        A[i] = B[i];
    }
    free(B);
}

void LsdRedixSort(int A[], int n){
    for(int d = 1; d < dn; d++){
        CountingSort(A, n, d);
    }
}

int main(){
    // int _source[] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36};
    int _source[] = {76, 11, 11, 43, 78, 35, 39, 27, 16, 55, 1, 41, 24, 19, 54, 7, 78, 69, 65, 82};
    int nCount = sizeof(_source) / sizeof(int);

    printf("Item count: %d\n", nCount);

    // srand(time(NULL));
    // for(int i = 0; i < 20; i++){
    //     _source[i] = rand() % 100;
    // }

    PA_DisplayData(_source, nCount);
    LsdRedixSort(_source, nCount);
    PA_DisplayData(_source, nCount);

    return 0;
}