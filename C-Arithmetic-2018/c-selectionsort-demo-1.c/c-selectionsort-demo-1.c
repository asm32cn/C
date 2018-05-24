// c-selectionsort-demo-1.c

#include <stdio.h>


void PA_DisplayData(int data[], int nCount){
    for(int i = 0; i < nCount; i++){
        if(i) printf(", ");
        printf("%d", data[i]);
    }
    printf("\n");
}

void Swap(int data[], int i, int j){
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

void SelectionSort(int data[], int n){
    for(int i = 0; i < n - 1; i++){
        int min = i;
        for(int j = i + 1; j < n; j++){
            if(data[j] < data[min]){
                min = j;
            }
        }
        if(min != i){
            Swap(data, min, i);
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
    //     data[i] = rand() % 100;
    // }

    PA_DisplayData(data, nCount);
    SelectionSort(data, nCount);
    PA_DisplayData(data, nCount);
}