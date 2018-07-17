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

/*
szSource:
	JavaCarsarDemo1.java (JAVA实现caesar凯撒加密算法)
pszEncrypt:
	MdydFduvduGhpr1.mdyd (MDYD实现fdhvdu凯撒加密算法)
pszDecrypt:
	JavaCarsarDemo1.java (JAVA实现caesar凯撒加密算法)
*/

/*
Carsar加密算法是最简单的加密算法，原理是把一个字母在字母表中移动相
应的位置，比如输入a，将其移动3位，经过Caesar加密后输出的d，位置可
以循环移动，输入x,则输出a
*/
