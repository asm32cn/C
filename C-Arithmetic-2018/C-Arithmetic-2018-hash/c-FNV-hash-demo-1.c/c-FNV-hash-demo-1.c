// c-FNV-hash-demo-1.c
#include <stdio.h>
#include <string.h>

#define M_MASK 31

int M_SHIFT = 0;

unsigned int FNVHash(char * pszKey){
	int nHash = 2166136261;
	int n = strlen(pszKey);
	for(int i = 0; i < n; i++){
		nHash = (nHash * 16777619) ^ pszKey[i];
	}
	if(M_SHIFT == 0)
		return nHash;
	return (nHash ^ (nHash >> M_SHIFT)) & M_MASK;
}

void main(){
	char * A_strKeys[] = {"C", "C++", "Java", "C#", "Python", "Go", "Scala", "vb.net", "JavaScript", "PHP", "Perl", "Ruby"};
	int nCount = sizeof(A_strKeys) / sizeof(char *);

	for(int i = 0; i < nCount; i++){
		unsigned int nHash = FNVHash(A_strKeys[i]);
		printf("%-10d %-15s %12lu %3d\n", i, A_strKeys[i], nHash, nHash % 31);
	}
}

/*
0          C                   84696412  10
1          C++               2219337286  11
2          Java              1542292725   7
3          C#                1316419575  18
4          Python            4101775411  26
5          Go                1249309159  14
6          Scala             4044407073   9
7          vb.net            3096269542  20
8          JavaScript        3504591080   5
9          PHP                589789791   4
10         Perl              3397136578  28
11         Ruby              3643069621  27
*/