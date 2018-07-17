// c-carsar-demo-1.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int CarserEncode(char * lpszSource, char * lpszTarget){
	char ch = 0,
		* pszSource = lpszSource,
		* pszTarget = lpszTarget;
	while(ch = *pszSource++){
		if(ch >= 'a' && ch <= 'z'){
			ch = 'a' + (ch - 'a' + 3) % 26;
		}else if(ch >= 'A' && ch <= 'Z'){
			ch = 'A' + (ch - 'A' + 3) % 26;
		}
		*pszTarget++ = ch;
	}
	*pszTarget = 0;
}

int CarserDecode(char * lpszSource, char * lpszTarget){
	char ch = 0,
		* pszSource = lpszSource,
		* pszTarget = lpszTarget;
	while(ch = *pszSource++){
		if(ch >= 'a' && ch <= 'z'){
			ch = 'a' + (ch - 'a' + 23) % 26;
		}else if(ch >= 'A' && ch <= 'Z'){
			ch = 'A' + (ch - 'A' + 23) % 26;
		}
		*pszTarget++ = ch;
	}
	*pszTarget = 0;
}

void main(){
	char szSource[] = "JavaCarsarDemo1.java (JAVA实现caesar凯撒加密算法)";
	int nCount = strlen(szSource) + 1;
	char* pszEncrypt = malloc(nCount);
	char* pszDecrypt = malloc(nCount);

	// memset(szEncrypt, 0, nCount)
	// memset(szDecrypt, 0, nCount)

	CarserEncode(szSource, pszEncrypt);
	CarserDecode(pszEncrypt, pszDecrypt);

	printf("szSource:\n\t%s\n", szSource);
	printf("pszEncrypt:\n\t%s\n", pszEncrypt);
	printf("pszDecrypt:\n\t%s\n", pszDecrypt);
}
