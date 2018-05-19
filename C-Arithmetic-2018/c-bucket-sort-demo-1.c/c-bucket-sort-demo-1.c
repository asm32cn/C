// c-bucket-sort-demo-1.c
#include <stdio.h>
#include <malloc.h>
// #include <time.h>

void PA_DisplayData(int data[], int nCount){
    for(int i = 0; i < nCount; i++){
        if(i) printf(", ");
        printf("%d", data[i]);
    }
    printf("\n");
}

#define MAX 100
#define bn 5

int nFactor = MAX % bn ? MAX / bn + 1 : MAX / bn;

int C[bn];

void InsertionSort(int data[], int left, int right){
    for(int i = left + 1; i <= right; i++){
        int get = data[i];
        int j = i - 1;
        while(j >= left && data[j] > get){
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = get;
    }
}

int MapToBucket(int x){
    return x / nFactor;
}

void CountingSort(int data[], int n){
    for(int i = 0; i < bn; i++){
        C[i] = 0;
    }
    for(int i = 0; i < n; i++){
        C[MapToBucket(data[i])]++;
    }
    for(int i = 1; i < bn; i++){
        C[i] = C[i] + C[i - 1];
    }
    int * B = (int *)malloc(n * sizeof(int));
    for(int i = n - 1; i >= 0; i--){
        int b = MapToBucket(data[i]);
        B[--C[b]] = data[i];
    }
    for(int i = 0; i < n; i++){
        data[i] = B[i];
    }
    free(B);
}

void BucketSort(int data[], int n){
    CountingSort(data, n);
    for(int i = 0; i < bn; i++){
        int left = C[i];
        int right = (i == bn - 1 ? n - 1 : C[i + 1] - 1); // C[i + 1] - 1为i号桶最后一个元素的位置
        if(left < right){
            InsertionSort(data, left, right);
        }
    }
}

void main(){
    // int data[] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36};
    int data[] = {76, 11, 11, 43, 78, 35, 39, 27, 16, 55, 1, 41, 24, 19, 54, 7, 78, 69, 65, 82};
    int nCount = sizeof(data) / sizeof(int);

    printf("Item count: %d\n", nCount);

    // srand(time(NULL));
    // for(int i = 0; i < 20; i++){
    //     data[i] = rand() % 1000;
    // }

    PA_DisplayData(data, nCount);
    BucketSort(data, nCount);
    PA_DisplayData(data, nCount);
}