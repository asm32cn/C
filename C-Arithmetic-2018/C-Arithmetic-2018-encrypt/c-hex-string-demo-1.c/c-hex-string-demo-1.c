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
		ch1 = (*pszSource++) % 48;
		ch2 = (*pszSource++) % 48;
		if(ch1 > 16) ch1 -= 7;
		if(ch2 > 16) ch2 -= 7;
		ch1 = ch1 & 15;
		ch2 = ch2 & 15;

		*pszTarget++ = (ch1 << 4) + ch2;
	}
	*pszTarget = 0;
}

void main(){
	unsigned char szData[] = "c-base64-demo-1.c\n程序中书写着所见所闻所感，编译着心中的万水千山。";
	int nCount = strlen(szData);
	unsigned char * pszHexStringEncode = malloc(nCount * 2 + 1);
	unsigned char * pszHexStringDecode = malloc(nCount + 1);

	HexStringEncode(szData, pszHexStringEncode);
	HexStringDecode(pszHexStringEncode, pszHexStringDecode);
	printf("%s\n%s\n%s\n", szData, pszHexStringEncode, pszHexStringDecode);
	free(pszHexStringEncode);
	free(pszHexStringDecode);
}

/*
c-base64-demo-1.c
程序中书写着所见所闻所感，编译着心中的万水千山。
632D6261736536342D64656D6F2D312E630AE7A88BE5BA8FE4B8ADE4B9A6E58699E79D80E68980E8A781E68980E997BBE68980E6849FEFBC8CE7BC96E8AF91E79D80E5BF83E4B8ADE79A84E4B887E6B0B4E58D83E5B1B1E38082
c-base64-demo-1.c
程序中书写着所见所闻所感，编译着心中的万水千山。
*/