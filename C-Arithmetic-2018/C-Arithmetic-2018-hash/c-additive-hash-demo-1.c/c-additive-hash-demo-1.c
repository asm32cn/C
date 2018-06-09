// c-additive-hash-demo-1.c
#include <stdio.h>
#include <string.h>

int AdditiveHash(char * pszKey, int nPrime){
	int nHash, i, n = strlen(pszKey);
	for(nHash = n, i = 0; i < n; i++){
		nHash += pszKey[i];
	}
	return nHash % nPrime;
}

void main(){
	char * A_strKeys[] = {"C", "C++", "Java", "C#", "Python", "Go", "Scala", "vb.net", "JavaScript", "PHP", "Perl", "Ruby"};
	int nCount = sizeof(A_strKeys) / sizeof(char *);

	for(int i = 0; i < nCount; i++){
		printf("%-10d %-15s %3d\n", i, A_strKeys[i], AdditiveHash(A_strKeys[i],31));
	}
}

/*
0          C                 6
1          C++               1
2          Java             18
3          C#               11
4          Python           28
5          Go               29
6          Scala            24
7          vb.net            6
8          JavaScript        2
9          PHP              18
10         Perl              4
11         Ruby             19
*/