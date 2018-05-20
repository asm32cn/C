// c-bucket-sort-demo-1.cpp
#include <iostream>
// #include <time.h>

using namespace std;

class BucketSortDemo1{
private:
	const static int MAX = 100;
	const static int bn = 5;
	const static int nFactor = MAX % bn ? MAX / bn + 1 : MAX / bn;
	int C[bn];

public:

	BucketSortDemo1(){}

	void PA_DisplayData(int data[], int nCount){
		for(int i = 0; i < nCount; i++){
			if(i) cout << ", ";
			cout << data[i];
		}
		cout << endl;
	}

	void InsertionSort(int A[], int nLeft, int nRight){
		for(int i = nLeft + 1; i <= nRight; i++){
			int nGet = A[i];
			int j = i - 1;
			while(j >= nLeft && A[j] > nGet){
				A[j + 1] = A[j];
				j--;
			}
			A[j + 1] = nGet;
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
		int * B = new int[n];
		for(int i = n - 1; i >= 0; i--){
			int b = MapToBucket(A[i]);
			B[--C[b]] = A[i];
		}
		for(int i = 0; i < n; i++){
			A[i] = B[i];
		}
		delete B;
	}

	void BucketSort(int A[], int n){
		CountingSort(A, n);
		for(int i = 0; i < bn; i++){
			int nLeft = C[i];
			int nRight = (i == bn - 1 ? n - 1 : C[i + 1] - 1); // C[i + 1] - 1为i号桶最后一个元素的位置
			if(nLeft < nRight){
				InsertionSort(A, nLeft, nRight);
			}
		}
	}
};

int main(){
	// int data[] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36};
	int data[] = {76, 11, 11, 43, 78, 35, 39, 27, 16, 55, 1, 41, 24, 19, 54, 7, 78, 69, 65, 82};
	int nCount = sizeof(data) / sizeof(int);

	cout << "Item count: " << nCount << endl;

	// srand(time(NULL));
	// for(int i = 0; i < 20; i++){
	//	 data[i] = rand() % 1000;
	// }

	BucketSortDemo1 * bsd = new BucketSortDemo1();

	bsd->PA_DisplayData(data, nCount);
	bsd->BucketSort(data, nCount);
	bsd->PA_DisplayData(data, nCount);

	delete bsd;
	
	return 0;
}