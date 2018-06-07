// c-format-currency-demo-1.c

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 255

void PA_FormatCurrency(char * pszSource, char * pszResult, int nSize){
	char * ps = pszSource;
	char * pr = pszResult;
	while(*ps){
		*pr++ = *ps++;
	}
}

void main(){
	char * A_strData[] = {"3.140009", "123456.5678", "1234567.5678", "-1234567.5678",
		"12345678.5678", "-12345678.5678", "123456789.5678", "-123456789.5678",
		"111113", "aa", "", "/", ".456", "-.456", "123aaa", "-123aaa", ".123aa",
		"-.123aa", "0.0", "-0.0", "0", "-0", "-", "0xa0", "12345678912.7654" /*, NULL*/};

	int nCount = sizeof(A_strData) / sizeof(char *);

	char szCache[MAX_SIZE] = {0};

	for(int i = 0; i < nCount; i++){
		memset(szCache, 0, MAX_SIZE);
		char * pszData = A_strData[i];
		PA_FormatCurrency(pszData, szCache, MAX_SIZE);
		printf("%d\t%20s\t%25s\n", i, pszData, szCache);
	}
}