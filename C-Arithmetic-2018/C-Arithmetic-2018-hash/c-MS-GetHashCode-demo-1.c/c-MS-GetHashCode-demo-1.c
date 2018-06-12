// c-MS-GetHashCode-demo-1.c
#include <stdio.h>
#include <string.h>

#define M_MASK 31

int M_SHIFT = 0;

unsigned long MS_GetHashCode(char * pszKey){
	int n = strlen(pszKey);
	char * pszData = pszKey;
	long nHash = 0x15051505;
	long nHash2 = nHash;
	int * pData = (int *)pszData;
	for(int i = n; i > 0; i -= 4){
		nHash = (((nHash << 5) + nHash) + (nHash >> 0x1b)) ^ pData[0];
		if(i <= 2) break;
		nHash2 = (((nHash2 << 5) + nHash2) + (nHash2 >> 0x1b)) ^ pData[1];
		pData += 2;
	}
	return (nHash + (nHash2 * 0x5d588b65));
}

void main(){
	char * A_strKeys[] = {"C", "C++", "Java", "C#", "Python", "Go", "Scala", "vb.net", "JavaScript", "PHP", "Perl", "Ruby"};
	int nCount = sizeof(A_strKeys) / sizeof(char *);

	for(int i = 0; i < nCount; i++){
		unsigned long nHash = MS_GetHashCode(A_strKeys[i]);
		printf("%-10d %-15s %12lu %3d\n", i, A_strKeys[i], nHash, nHash % 31);
	}
}

/*
0          C                 3070736349   8
1          C++               3848949605  21
2          Java               412864976   1
3          C#                4257913053  30
4          Python             275626405  11
5          Go                4274707673  28
6          Scala             3561231455   1
7          vb.net             666464023  14
8          JavaScript        1507798302  28
9          PHP               1337035882  23
10         Perl              3493520090  14
11         Ruby              3093528536   3
*/