// c-radix-sort-demo-1.cpp
#include <iostream>

using namespace std;

class LsdRedixSortDemo1{
private:
    const static int dn = 3;
    const static int k = 10;
    int C[k];

public:
    void PA_DisplayData(int data[], int nCount){
        for(int i = 0; i < nCount; i++){
            if(i) cout << ", ";
            cout << data[i];
        }
        cout << endl;
    }

    void CountingSort(int A[], int n, int d){
        for(int i = 0; i < k; i++){
            C[i] = 0;
        }
        for(int i = 0; i < n; i++){
            C[GetDigit(A[i], d)]++;
        }
        for(int i = 1; i < k; i++){
            C[i] = C[i] + C[i - 1];
        }
        int *B = new int[n];
        for(int i = n - 1; i >= 0; i--){
            int dight = GetDigit(A[i], d);
            B[--C[dight]] = A[i];
        }
        for(int i = 0; i < n; i++){
            A[i] = B[i];
        }
        delete B;
    }

    void LsdRedixSort(int A[], int n){
        for(int d = 1; d < dn; d++){
            CountingSort(A, n, d);
        }
    }

private:
    int GetDigit(int x, int d){
        int radix[] = {1, 1, 10, 100};
        return (x / radix[d]) % 10;
    }
};

int main(){
    // int _source[] = {41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61, 91, 95, 42, 27, 36};
    int _source[] = {76, 11, 11, 43, 78, 35, 39, 27, 16, 55, 1, 41, 24, 19, 54, 7, 78, 69, 65, 82};
    int nCount = sizeof(_source) / sizeof(int);

    cout << "Item count: " << nCount << endl;

    // srand(time(NULL));
    // for(int i = 0; i < 20; i++){
    //     _source[i] = rand() % 100;
    // }

    LsdRedixSortDemo1 * lrsd = new LsdRedixSortDemo1();

    lrsd->PA_DisplayData(_source, nCount);
    lrsd->LsdRedixSort(_source, nCount);
    lrsd->PA_DisplayData(_source, nCount);

    delete lrsd;

    return 0;
}