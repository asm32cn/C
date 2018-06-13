// c-JSHash-demo-1.c
#include <stdio.h>
#include <string.h>

unsigned int JSHash(char * pszKey){
	unsigned int nHash = 1315423911;

	while(*pszKey){
		nHash ^= ((nHash << 5) + (*pszKey++) + (nHash >> 2));
	}

	return nHash & 0x7FFFFFFF;
}

void main(){
	char * A_strKeys[] = {"C", "C++", "Java", "C#", "Python", "Go", "Scala", "vb.net", "JavaScript", "PHP", "Perl", "Ruby"};
	int nCount = sizeof(A_strKeys) / sizeof(char *);

	for(int i = 0; i < nCount; i++){
		unsigned int uiHash = JSHash(A_strKeys[i]);
		printf("%-10d %-15s %11u %3d\n", i, A_strKeys[i], uiHash, uiHash % 31 );
	}
}

/*
0          C                 787808363   0
1          C++               446398608   3
2          Java             1082641991   6
3          C#                615009782   7
4          Python           1495460415  17
5          Go                615010075  21
6          Scala            1696237482   4
7          vb.net             59114926   3
8          JavaScript         35438201  24
9          PHP               446451679   2
10         Perl             1085069648  22
11         Ruby             1084837418  13
*/