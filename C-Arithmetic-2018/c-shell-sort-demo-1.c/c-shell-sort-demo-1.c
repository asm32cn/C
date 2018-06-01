// c-shell-sort-demo-1.c
#include <stdio.h>

void PA_DisplayData(int data[], int nCount){
	for(int i = 0; i < nCount; i++){
		if(i) printf(", ");
		printf("%d", data[i]);
	}
	printf("\n");
}

void ShellSort(int data[], int n){
	int h = 0;
	while(h <= n){
		h = 3 * h + 1;
	}
	while(h >= 1){
		for(int i = h; i < n; i++){
			int j = i - h;
			int nGet = data[i];
			while(j >= 0 && data[j] > nGet){
				data[j + h] = data[j];
				j = j - h;
			}
			data[j + h] = nGet;
		}
		h = (h - 1) / 3;
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
	ShellSort(data, nCount);
	PA_DisplayData(data, nCount);
}