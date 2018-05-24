// c-merge-sort-demo-1.c

#include <stdio.h>
#include <malloc.h>
// #include <limits.h>

void PA_DisplayData(int data[], int nCount){
    for(int i = 0; i < nCount; i++){
        if(i) printf(", ");
        printf("%d", data[i]);
    }
    printf("\n");
}

void Merge(int data[], int left, int mid, int right){
    int len = right - left + 1;
    int *temp = malloc(sizeof(int) * len);
    int index = 0;
    int i = left;
    int j = mid + 1;
    while(i <= mid && j <= right){
        temp[index++] = data[i] <= data[j] ? data[i++] : data[j++];
    }
    while(i <= mid){
        temp[index++] = data[i++];
    }
    while(j <= right){
        temp[index++] = data[j++];
    }
    for(int k = 0; k < len; k++){
        data[left++] = temp[k];
    }
}

// 递归实现的归并排序(自顶向下)
void MergeSortRecursion(int data[], int left, int right){
    // 当待排序的序列长度为1时，递归开始回溯，进行merge操作
    if(left == right) return;

    int mid = (left + right) / 2;
    MergeSortRecursion(data, left, mid);
    MergeSortRecursion(data, mid + 1, right);
    Merge(data, left, mid, right);
}

// 非递归(迭代)实现的归并排序(自底向上)
void MergeSortIteration(int data[], int len){
    // 子数组索引，前一个为A[left ... mid]，后一个为A[mid + 1 ... right]
    int left, mid, right;
    // 子数组的大小i初始为1，没轮翻倍
    for(int i = 1; i < len; i *= 2){
        left = 0;
        // 后一个子数组存在(需要归并)
        while(left + i < len){
            mid = left + i - 1;
            // 后一个子数组大小可能不够
            right = mid + i < len ? mid + i : len - 1;
            Merge(data, left, mid, right);
            // 前一个子数组索引向后移动
            left = right + 1;
        }
    }
}

void main(){
    // int data[] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36};
    int data1[] = {76, 11, 11, 43, 78, 35, 39, 27, 16, 55, 1, 41, 24, 19, 54, 7, 78, 69, 65, 82};
    int data2[] = {76, 11, 11, 43, 78, 35, 39, 27, 16, 55, 1, 41, 24, 19, 54, 7, 78, 69, 65, 82};
    int nCount1 = sizeof(data1) / sizeof(int);
    int nCount2 = sizeof(data2) / sizeof(int);
    
    // srand(time(NULL));
    // for(int i = 0; i < 20; i++){
    //     data[i] = rand() % 100;
    // }

    printf("Item count: %d\n", nCount1);
    PA_DisplayData(data1, nCount1);
    MergeSortRecursion(data1, 0, nCount1 - 1);
    PA_DisplayData(data1, nCount1);

    printf("Item count: %d\n", nCount2);
    PA_DisplayData(data2, nCount2);
    MergeSortIteration(data2, nCount2);
    PA_DisplayData(data2, nCount2);
}