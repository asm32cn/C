// c-BKDRHash-demo-1.c
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
0          C                        67   5
1          C++                 1155463   0
2          Java              168038906  27
3          C#                     8812   8
4          Python           1962499928   9
5          Go                     9412  19
6          Scala            1045413186   0
7          vb.net            763463135   2
8          JavaScript        557701633   8
9          PHP                 1382392   9
10         Perl              181595583   1
11         Ruby              186364258   8
*/