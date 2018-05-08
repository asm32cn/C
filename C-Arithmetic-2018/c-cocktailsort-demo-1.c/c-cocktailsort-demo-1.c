// c-cocktailsort-demo-1.c

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

void CocktailSort(int A[], int n){
    int left = 0;
    int right = n - 1;
    while(left < right){
        for(int i = left; i < right; i++){
            if(A[i] > A[i + 1]){
                Swap(A, i, i + 1);
            }
        }
        right--;
        for(int i = right; i > left; i--){
            if(A[i - 1] > A[i]){
                Swap(A, i - 1, i);
            }
        }
        left++;
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
    CocktailSort(_source, nCount);
    PA_DisplayData(_source, nCount);

    return 0;
}