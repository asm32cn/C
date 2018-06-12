// c-FNV1-hash-demo-1.c
#include <stdio.h>
#include <string.h>

unsigned int FNVHash1(char * pszKey){
	int n = strlen(pszKey);
	long p = 1677619;
	unsigned long nHash = 2166136261;
	for(int i = 0; i < n; i++){
		nHash = (nHash ^ pszKey[i]) * p;
	}
	nHash += nHash << 13;
	nHash ^= nHash >> 7;
	nHash += nHash << 3;
	nHash ^= nHash >> 17;
	nHash += nHash << 5;
	return nHash;
}

void main(){
	char * A_strKeys[] = {"C", "C++", "Java", "C#", "Python", "Go", "Scala", "vb.net", "JavaScript", "PHP", "Perl", "Ruby"};
	int nCount = sizeof(A_strKeys) / sizeof(char *);

	for(int i = 0; i < nCount; i++){
		unsigned int nHash = FNVHash1(A_strKeys[i]);
		printf("%-10d %-15s %12lu %3d\n", i, A_strKeys[i], nHash, nHash % 31);
	}
}

/*
0          C                 2196503546   3
1          C++               2331617826   8
2          Java                 8810697   1
3          C#                3069945261   9
4          Python            2130055597  27
5          Go                3741730183  20
6          Scala             1222329954  16
7          vb.net            3093588254  15
8          JavaScript          85664180  20
9          PHP               1137923497  18
10         Perl              2787627348  26
11         Ruby              3352852179  28
*/