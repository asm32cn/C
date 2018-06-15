// c-MS-GetHashCode-demo-1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_MASK 31

int M_SHIFT = 0;

unsigned long MS_GetHashCode(char * pszKey){
	int n = strlen(pszKey);
	int nSizeInt = sizeof(int);
	int m = n + nSizeInt;
	char * szData = malloc(m);
	memset(szData, 0, m);
	strcpy(szData, pszKey);

	char * pszData = szData;
	long nHash = 0x15051505;
	long nHash2 = nHash;
	int * pData = (int *)pszData;
	for(int i = n; i > 0; i -= nSizeInt + nSizeInt){
		nHash = (((nHash << 5) + nHash) + (nHash >> 0x1b)) ^ pData[0];
		if(i <= nSizeInt) break;
		nHash2 = (((nHash2 << 5) + nHash2) + (nHash2 >> 0x1b)) ^ pData[1];
		pData += 2;
	}
	free(szData);
	return (nHash + (nHash2 * 0x5d588b65));
}

void main(){
	char * A_strKeys[] = {"C", "C++", "Java", "C#", "Python", "Go", "Scala", "vb.net", "JavaScript", "PHP", "Perl", "Ruby"};
	int nCount = sizeof(A_strKeys) / sizeof(char *);

	for(int i = 0; i < nCount; i++){
		unsigned long nHash = MS_GetHashCode(A_strKeys[i]);
		printf("%-10d %-15s %12lu %3d\n", i, A_strKeys[i], nHash, nHash % 33);
	}
}

/*
0          C                 3452614621  16
1          C++               3450839261  23
2          Java              3975468774  24
3          C#                3452606685   0
4          Python            3793951455  30
5          Go                3452624089  13
6          Scala             4273213458  30
7          vb.net            2979897179  17
8          JavaScript         855658811  29
9          PHP               3457875952  25
10         Perl              4059615984   6
11         Ruby              3840459502  22
*/