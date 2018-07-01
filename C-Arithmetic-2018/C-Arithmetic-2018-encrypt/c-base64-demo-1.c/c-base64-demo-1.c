// c-base64-demo-1.c
#include <stdio.h>

const unsigned char szHexDigit[] = "0123456789ABCDEF";
const unsigned char szKey[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

void DisplayHexString(unsigned char * pszData){
	unsigned char ch, * psz = pszData;
	unsigned char szLine[100] = {0};
	int n = 0, nCol = 0, nOffset = 0;

	for(int i = 0; i < 64; i++) szLine[i] = 32;
	szLine[23] = '-';
	szLine[64] = 10;
	while(ch = *psz++){
		nCol = n % 16;
		if(n && nCol == 0){
			printf(szLine);
			for(int i = 0; i < 64; i++) szLine[i] = 32;
			szLine[23] = '-';
			nOffset = 0;
		}

		szLine[nOffset] = szHexDigit[ch >> 4];
		szLine[nOffset + 1] = szHexDigit[ch % 16];
		szLine[nCol + 48] = ch < 32 || ch > 127 ? '.' : ch;
		nOffset += 3;
		n++;
	}
	if(nCol){
		printf(szLine);
	}
}

void main(){
	unsigned char * pszData = "go-base64-demo-1.go\n程序中书写着所见所闻所感，编译着心中的万水千山。";
	printf("c-base64-demo-1.c\n");
	DisplayHexString(pszData);
	printf("%s\n", pszData);
}

