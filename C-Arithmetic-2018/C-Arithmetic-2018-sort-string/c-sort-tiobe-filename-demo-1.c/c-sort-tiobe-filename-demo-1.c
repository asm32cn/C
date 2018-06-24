// c-sort-tiobe-filename-demo-1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * A_pszMonths[] = {"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"};

void SortFileName(char ** pszFiles, char** pszSorted, int nCount);

void main(){
	char * A_pszFiles[] = {"TIOBE Index for April 2018.html",
		"TIOBE Index for February 2018.html",
		"TIOBE Index for January 2018.html",
		"TIOBE Index for June 2018.html",
		"TIOBE Index for March 2018.html",
		"TIOBE Index for May 2018.html",
		"TIOBE-exchange-matrix-data.html",
		"TIOBE-exchange-matrix-data.py",
		"TIOBE-gernate-index-py2.py",
		"TIOBE-index.html",
		"TIOBE_matrixData.txt"};
	int nCount = sizeof(A_pszFiles) / sizeof(char *);
	char ** A_pszSorted = (char **) malloc(sizeof(char *) * nCount);

	SortFileName(A_pszFiles, A_pszSorted, nCount);

	printf("@  %-36s %-36s\n", "Source data", "Sorted data");
	printf("== %-36s %-36s\n", "==================", "==================");
	for(int i = 0; i < nCount; i++){
		printf("%-2d %-36s %-36s\n", i, A_pszFiles[i], A_pszSorted[i]);
	}
}

int GetIndex(int * data, int i){
	return data[i * 3 + 1];
}

void SetIndex(int * data, int i, int n){
	data[i * 3 + 1] = n;
}

int GetData(int * data, int i){
	return data[GetIndex(data, i) * 3 + 2];
}

int GetDataspan(char * s, int * n){
	int mm = 0, yy = 0, len = strlen(s);
	char * matcher[] = {"TIOBE Index for ", ".html"};
	int matcher_len[] = {strlen(matcher[0]), strlen(matcher[1])};
	char ch, * psz1 = s, * psz2 = matcher[0];
	char cache[len + 1];
	int i = 0, nDatespan;
	while(*psz1 && *psz2++ == *psz1++) i++;
	if(i == matcher_len[0]){
		nDatespan = 0;
		// scan month
		for(i = 0, psz1--; (ch = *psz1++) && (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z'); i++);
		if(i > 0){
			memset(cache, 0, len + 1);
			strncpy(cache, s + matcher_len[0], i);
			for(int j = 0; j < 12; j++){
				if(strcmp(cache, A_pszMonths[j]) == 0){
					mm = j + 1;
					break;
				}
			}
			if(ch == ' '){
				// scan year
				for(i= 0, psz2 = psz1; (ch = *psz1++) && (ch >= '0' && ch <= '9'); i++);
				if(i == 4){
					memset(cache, 0, len + 1);
					strncpy(cache, psz2, 4);
					yy = atoi(cache);

					for(i = 0, psz2 = matcher[1], psz1--; *psz1 && *psz2 && *psz1++ == *psz2++; i++);
					if(i == matcher_len[1]){
						nDatespan = yy * 100 + mm;
					}
				}
			}
		}
	}else{
		nDatespan = ++(*n);
	}
	// printf("%-35s %4d %3d %3d %6d\n", s, yy, mm, *n, nDatespan);
	return nDatespan;
}

void SortFileName(char ** pszFiles, char ** pszSorted, int nCount){
	int * buff = (int *)malloc(sizeof(int) * 3 * nCount);

	// init buff
	int n = 0;
	for(int i = 0; i < nCount; i++){
		int nOffset = i * 3;
		buff[nOffset + 0] = buff[nOffset + 1] = i;
		buff[nOffset + 2] = GetDataspan(pszFiles[i], &n);
	}

	// sort data
	for(int i = 0; i < nCount - 1; i++){
		int nMin = i;
		for(int j = i + 1; j < nCount; j++){
			if(GetData(buff, j) < GetData(buff, nMin)){
				nMin = j;
			}
		}
		if(i != nMin){
			int t = GetIndex(buff, i);
			SetIndex(buff, i, GetIndex(buff, nMin));
			SetIndex(buff, nMin, t);
		}
	}

	// write result
	for(int i = 0; i < nCount; i++){
		pszSorted[i] = pszFiles[GetIndex(buff, i)];
	}
	free(buff);
}

/*
@  Source data                          Sorted data
== ==================                   ==================
0  TIOBE Index for April 2018.html      TIOBE-exchange-matrix-data.html
1  TIOBE Index for February 2018.html   TIOBE-exchange-matrix-data.py
2  TIOBE Index for January 2018.html    TIOBE-gernate-index-py2.py
3  TIOBE Index for June 2018.html       TIOBE-index.html
4  TIOBE Index for March 2018.html      TIOBE_matrixData.txt
5  TIOBE Index for May 2018.html        TIOBE Index for January 2018.html
6  TIOBE-exchange-matrix-data.html      TIOBE Index for February 2018.html
7  TIOBE-exchange-matrix-data.py        TIOBE Index for March 2018.html
8  TIOBE-gernate-index-py2.py           TIOBE Index for April 2018.html
9  TIOBE-index.html                     TIOBE Index for May 2018.html
10 TIOBE_matrixData.txt                 TIOBE Index for June 2018.html
*/