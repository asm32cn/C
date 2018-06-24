// c-sort-filename-demo-1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * A_pszMonths[] = {"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"};

void sortFileName(char ** pszFiles, char** pszSorted, int nCount);

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

	sortFileName(A_pszFiles, A_pszSorted, nCount);

	printf("@  %-36s %-36s\n", "Source data", "Sorted data");
	printf("== %-36s %-36s\n", "==================", "==================");
	for(int i = 0; i < nCount; i++){
		printf("%-2d %-36s %-36s\n", i, A_pszFiles[i], A_pszSorted[i]);
	}
}

int getIndex(int * data, int i){
	return data[i * 3 + 1];
}

void setIndex(int * data, int i, int n){
	data[i * 3 + 1] = n;
}

int getData(int * data, int i){
	return data[getIndex(data, i) * 3 + 2];
}

int getDataspan(char * s, int * n){
	int mm = 0, yy = 0, len = strlen(s);
	char * matcher[] = {"TIOBE Index for ", ".html"};
	int matcher_len[] = {strlen(matcher[0]), strlen(matcher[1])};
	char ch, * psz1 = s, * psz2 = matcher[0];
	char cache[len + 1];
	int i = 0, nDatespan;
	while(*psz2++ == *psz1++) i++;
	if(i == matcher_len[0]){
		nDatespan = 0;
		// scan month
		while((ch = *psz1++) && (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')) mm++;
		if(mm > 0){
			memset(cache, 0, len + 1);
			strncpy(cache, s + matcher_len[0], mm + 1);
			for(int j = 0; j < 12; j++){
				if(strcmp(cache, A_pszMonths[j]) == 0){
					mm = j + 1;
					break;
				}
			}
			if(ch == ' '){
				// scan year
				psz2 = psz1;
				while((ch = *psz1++) && (ch >= '0' && ch <= '9')) yy++;
				if(yy > 0){
					memset(cache, 0, len + 1);
					strncpy(cache, psz2, 4);
					yy = atoi(cache);

					psz1--;
					psz2 = matcher[1];
					i = 0;
					while(*psz1 && *psz2 && *psz1++ == *psz2++) i++;
					if(i == matcher_len[1]){
						nDatespan = yy * 100 + mm;
					}
				}
			}
		}
	}else{
		nDatespan = (*n)++;
	}
	// printf("%-35s %3d %3d %3d\n", s, i, *n, nDatespan);
	return nDatespan;
}

void sortFileName(char ** pszFiles, char ** pszSorted, int nCount){
	int * buff = (int *)malloc(sizeof(int) * 3 * nCount);

	// init buff
	int n = 0;
	for(int i = 0; i < nCount; i++){
		int nOffset = i * 3;
		buff[nOffset + 0] = buff[nOffset + 1] = i;
		buff[nOffset + 2] = getDataspan(pszFiles[i], &n);
	}

	// sort data
	for(int i = 0; i < nCount - 1; i++){
		int nMin = i;
		for(int j = i + 1; j < nCount; j++){
			if(getData(buff, j) < getData(buff, nMin)){
				nMin = j;
			}
		}
		if(i != nMin){
			int t = getIndex(buff, i);
			setIndex(buff, i, getIndex(buff, nMin));
			setIndex(buff, nMin, t);
		}
	}

	// gernate result
	for(int i = 0; i < nCount; i++){
		pszSorted[i] = pszFiles[getIndex(buff, i)];
		// printf("%d %d %d\n", buff[i * 3 + 0], buff[i * 3 + 1], buff[i * 3 + 2]);
		// pszSorted[i] = pszFiles[i];
	}
	free(buff);
	// return pszFiles;
}