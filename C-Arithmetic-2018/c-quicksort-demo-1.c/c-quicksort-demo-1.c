// c-quicksort-demo-1.c

#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

void PA_DisplayData(int data[], int nCount){
    for(int i = 0; i < nCount; i++){
        if(i) printf(", ");
        printf("%d", data[i]);
    }
    printf("\n");
}

void QuickSort(int data[], int nLeft, int nRight){
    if(nLeft < nRight){
        int nKey = data[nLeft];
        int nLow = nLeft;
        int nHigh = nRight;
        while(nLow < nHigh){
            while(nLow < nHigh && data[nHigh] >= nKey){
                nHigh--;
            }
            data[nLow] = data[nHigh];
            while(nLow < nHigh && data[nLow] <= nKey){
                nLow++;
            }
            data[nHigh] = data[nLow];
        }
        data[nLow] = nKey;

        QuickSort(data, nLeft, nLow - 1);
        QuickSort(data, nLow + 1, nRight);
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
    QuickSort(_source, 0, nCount - 1);
    PA_DisplayData(_source, nCount);
}