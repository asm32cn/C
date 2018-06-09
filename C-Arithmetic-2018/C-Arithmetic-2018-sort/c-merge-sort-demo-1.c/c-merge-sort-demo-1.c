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

void Merge(int data[], int nLeft, int nMid, int nRight){
	int nLen = nRight - nLeft + 1;
	int *temp = malloc(sizeof(int) * nLen);
	int nIndex = 0;
	int i = nLeft;
	int j = nMid + 1;
	while(i <= nMid && j <= nRight){
		temp[nIndex++] = data[i] <= data[j] ? data[i++] : data[j++];
	}
	while(i <= nMid){
		temp[nIndex++] = data[i++];
	}
	while(j <= nRight){
		temp[nIndex++] = data[j++];
	}
	for(int k = 0; k < nLen; k++){
		data[nLeft++] = temp[k];
	}
}

// 递归实现的归并排序(自顶向下)
void MergeSortRecursion(int data[], int nLeft, int nRight){
	// 当待排序的序列长度为1时，递归开始回溯，进行merge操作
	if(nLeft == nRight) return;

	int nMid = (nLeft + nRight) / 2;
	MergeSortRecursion(data, nLeft, nMid);
	MergeSortRecursion(data, nMid + 1, nRight);
	Merge(data, nLeft, nMid, nRight);
}

// 非递归(迭代)实现的归并排序(自底向上)
void MergeSortIteration(int data[], int nLen){
	// 子数组索引，前一个为A[nLeft ... nMid]，后一个为A[nMid + 1 ... nRight]
	int nLeft, nMid, nRight;
	// 子数组的大小i初始为1，每轮翻倍
	for(int i = 1; i < nLen; i *= 2){
		nLeft = 0;
		// 后一个子数组存在(需要归并)
		while(nLeft + i < nLen){
			nMid = nLeft + i - 1;
			// 后一个子数组大小可能不够
			nRight = nMid + i < nLen ? nMid + i : nLen - 1;
			Merge(data, nLeft, nMid, nRight);
			// 前一个子数组索引向后移动
			nLeft = nRight + 1;
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
	//	 data[i] = rand() % 100;
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