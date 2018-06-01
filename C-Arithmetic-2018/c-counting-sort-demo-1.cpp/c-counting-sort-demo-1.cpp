// c-counting-sort-demo-1.cpp
#include <iostream>

using namespace std;

class CountingSortDemo1{
private:
	const static int k = 100;
	int C[k];
public:
	void PA_DisplayData(int data[], int nCount){
		for(int i = 0; i < nCount; i++){
			if(i) cout << ", ";
			cout << data[i];
		}
		cout << endl;
	}

	void CountingSort(int data[], int n){
		for(int i = 0; i < k; i++){
			C[i] = 0;
		}
		for(int i = 0; i < n; i++){
			C[data[i]]++;
		}
		for(int i = 1; i < k; i++){
			C[i] = C[i] + C[i - 1];
		}
		int *B = new int[n];
		for(int i = n - 1; i >= 0; i--){
			B[--C[data[i]]] = data[i];
		}
		for(int i = 0; i < n; i++){
			data[i] = B[i];
		}
		delete B;
	}
};

int main(){
	// int data[] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36};
	int data[] = {76, 11, 11, 43, 78, 35, 39, 27, 16, 55, 1, 41, 24, 19, 54, 7, 78, 69, 65, 82};
	int nCount = sizeof(data) / sizeof(int);

	cout << "Item count: " << nCount << endl;

	// srand(time(NULL));
	// for(int i = 0; i < 20; i++){
	//     data[i] = rand() % 100;
	// }

	CountingSortDemo1 * csd = new CountingSortDemo1();

	csd->PA_DisplayData(data, nCount);
	csd->CountingSort(data, nCount);
	csd->PA_DisplayData(data, nCount);

	delete csd;

	return 0;
}