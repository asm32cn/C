// c-format-currency-demo-1.c

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 255

void PA_FormatCurrency(char * pszSource, char * pszResult, int nSize){
	char * pszCache = malloc(MAX_SIZE);
	double d = atof(pszSource);

	memset(pszCache, 0, MAX_SIZE);
	sprintf(pszCache, "%.2lf", d);
	int lc = strlen(pszCache);

	if( *pszCache == '-' ){
		*pszResult++ = '-';
		pszCache++;
		lc--;
	}

	if(lc > 6){
		int st = lc % 3;
		for(int i = 0; i < lc; i++){
			if(i && i <= lc - 6 && (i - st) % 3 == 0){
				*pszResult++ = ',';
			}
			*pszResult++ = pszCache[i];
		}
	}else{
		strcpy(pszResult, pszCache);
	}
}

void main(){
	char * A_strData[] = {"3.140009", "123456.5678", "1234567.5678", "-1234567.5678",
		"12345678.5678", "-12345678.5678", "123456789.5678", "-123456789.5678",
		"111113", "aa", "", "/", ".456", "-.456", "123aaa", "-123aaa", ".123aa",
		"-.123aa", "0.0", "-0.0", "0", "-0", "-", "0xa0", "12345678912345.7654" /*, NULL*/};

	int nCount = sizeof(A_strData) / sizeof(char *);

	char szCache[MAX_SIZE] = {0};

	for(int i = 0; i < nCount; i++){
		memset(szCache, 0, MAX_SIZE);
		char * pszData = A_strData[i];
		PA_FormatCurrency(pszData, szCache, MAX_SIZE);
		printf("%d\t%20s\t%25s\n", i, pszData, szCache);
	}
}

/*
0                   3.140009                         3.14
1                123456.5678                   123,456.57
2               1234567.5678                 1,234,567.57
3              -1234567.5678                -1,234,567.57
4              12345678.5678                12,345,678.57
5             -12345678.5678               -12,345,678.57
6             123456789.5678               123,456,789.57
7            -123456789.5678              -123,456,789.57
8                     111113                   111,113.00
9                         aa                         0.00
10                                                   0.00
11                         /                         0.00
12                      .456                         0.46
13                     -.456                        -0.46
14                    123aaa                       123.00
15                   -123aaa                      -123.00
16                    .123aa                         0.12
17                   -.123aa                        -0.12
18                       0.0                         0.00
19                      -0.0                        -0.00
20                         0                         0.00
21                        -0                        -0.00
22                         -                         0.00
23                      0xa0                         0.00
24       12345678912345.7654        12,345,678,912,345.77
*/