// c-RSHash-demo-1.c
#include <stdio.h>
#include <string.h>

unsigned long RSHash(char * pszKey){
	int n = strlen(pszKey);
	int b = 378551;
	int a = 63689;
	unsigned long nHash = 0;
	for(int i = 0; i < n; i++){
		nHash = nHash * a + pszKey[i];
		a = a * b;
	}
	return nHash & 0x7FFFFFFF;
}

void main(){
	char * A_strKeys[] = {"C", "C++", "Java", "C#", "Python", "Go", "Scala", "vb.net", "JavaScript", "PHP", "Perl", "Ruby"};
	int nCount = sizeof(A_strKeys) / sizeof(char *);

	for(int i = 0; i < nCount; i++){
		unsigned long nHash = RSHash(A_strKeys[i]);
		printf("%-10d %-15s %12lu %3d\n", i, A_strKeys[i], nHash, nHash % 31);
	}
}

/*
0          C                         67   5
1          C++               1535458403   7
2          Java              1675714860   2
3          C#                 431117552  25
4          Python             481257876  19
5          Go                 232492024  22
6          Scala             1047644580  14
7          vb.net             550038443  18
8          JavaScript         711855001  17
9          PHP               1664999048  22
10         Perl               340008717   4
11         Ruby               677893036   9
*/