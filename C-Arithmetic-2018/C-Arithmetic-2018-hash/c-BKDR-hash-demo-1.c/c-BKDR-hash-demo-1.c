// c-BKDR-hash-demo-1.c
#include <stdio.h>
#include <string.h>

unsigned int BKDRHash(char * pszKey){
	unsigned int nSeed = 131; // 31 131 1313 13131 131313 etc
	unsigned int nHash = 0;
	while(*pszKey){
		nHash = nHash * nSeed + *pszKey++;
	}

	return nHash & 0x7FFFFFFF;
}

void main(){
	char * A_strKeys[] = {"C", "C++", "Java", "C#", "Python", "Go", "Scala", "vb.net", "JavaScript", "PHP", "Perl", "Ruby"};
	int nCount = sizeof(A_strKeys) / sizeof(char *);

	for(int i = 0; i < nCount; i++){
		unsigned int uiHash = BKDRHash(A_strKeys[i]);
		printf("%-10d %-15s %11u %3d\n", i, A_strKeys[i], uiHash, uiHash % 31 );
	}
}

/*
0          C                 6   5
1          C++               1  12
2          Java             18   4
3          C#               11   4
4          Python           28  17
5          Go               29  18
6          Scala            24   4
7          vb.net            6  23
8          JavaScript        2  23
9          PHP              18  18
10         Perl              4  15
11         Ruby             19  28
*/