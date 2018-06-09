// c-additive-hash-demo-1.c
#include <stdio.h>
#include <string.h>

int additiveHash(char * pszKey, int nPrime){
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
		printf("%2d %12s %10d\n", i, A_strKeys[i], additiveHash(A_strKeys[i],31));
	}
}