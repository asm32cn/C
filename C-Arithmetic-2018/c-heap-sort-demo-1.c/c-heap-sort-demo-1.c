// c-heap-sort-demo-1.c
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

void Heapify(int data[], int i, int nSize){
	int nLeftChild = 2 * i + 1;
	int nRightChild = 2 * i + 2;
	int nMax = i;
	if(nLeftChild < nSize && data[nLeftChild] > data[nMax]){
		nMax = nLeftChild;
	}
	if(nRightChild < nSize && data[nRightChild] > data[nMax]){
		nMax = nRightChild;
	}
	if(nMax != i){
		Swap(data, i, nMax);
		Heapify(data, nMax, nSize);
	}
}

int BuildHeap(int data[], int n){
	int nHeapSize = n;
	for(int i = nHeapSize / 2 - 1; i >= 0; i--){
		Heapify(data, i, nHeapSize);
	}
	return nHeapSize;
}

void HeapSort(int data[], int n){
	int nHeapSize = BuildHeap(data, n);
	while(nHeapSize > 1){
		Swap(data, 0, --nHeapSize);
		Heapify(data, 0, nHeapSize);
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
	HeapSort(data, nCount);
	PA_DisplayData(data, nCount);
}