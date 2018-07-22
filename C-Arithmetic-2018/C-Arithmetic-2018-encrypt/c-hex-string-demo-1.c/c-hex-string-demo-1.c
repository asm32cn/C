// c-hex-string-demo-1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned char szHexDigit[] = "0123456789ABCDEF";

void HexStringEncode(unsigned char * lpszSource, unsigned char * lpszTarget){
	unsigned char * pszSource = lpszSource, * pszTarget = lpszTarget;
	unsigned char ch;
	while(ch = *pszSource++){
		*pszTarget++ = szHexDigit[(ch & 0xf0) >> 4];
		*pszTarget++ = szHexDigit[ch & 15];
	}
	*pszTarget = 0;
}

void HexStringDecode(unsigned char * lpszSource, unsigned char * lpszTarget){
	unsigned char * pszSource = lpszSource, * pszTarget = lpszTarget;
	unsigned char ch1, ch2;
	while(*pszSource){
		ch1 = *pszSource++;
		ch2 = *pszSource++;
		// ch1 
	}
}

void main(){
	unsigned char szData[] = "c-base64-demo-1.c\n程序中书写着所见所闻所感，编译着心中的万水千山。";
	int nCount = strlen(szData);
	unsigned char * pszHexStringEncode = malloc(nCount * 2 + 1);
	unsigned char * pszHexStringDecode = malloc(nCount + 1);

	HexStringEncode(szData, pszHexString);
	printf("%s\n%s\n", szData, pszHexString);
	free(pszHexString);
}
