// c-base64-demo-1.c   2018-07-01 02:41:48
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int Base64Encode(char* lpszData, char* lpszEncrypt){
	unsigned char chr1 = 0, chr2 = 0, chr3 = 0;
	unsigned char enc1 = 0, enc2 = 0, enc3 = 0, enc4 = 0;
	int i = 0, nCount = strlen(lpszData);
	unsigned char * pszEncrypt = lpszEncrypt;
	while(i < nCount){
		chr1 = lpszData[i++];
		enc1 = chr1 >> 2;
		if(i < nCount){
			chr2 = lpszData[i++];
			enc2 = ((chr1 & 3) << 4) | ((chr2 & 0xf0) >> 4);
			if(i < nCount){
				chr3 = lpszData[i++];
				enc3 = ((chr2 & 15) << 2) | ((chr3 & 0xc0) >> 6);
				enc4 = chr3 & 63;
			}else{
				enc3 = (chr2 & 15) << 2;
				enc4 = 64;
			}
		}else{
			enc2 = (chr1 & 3) << 4;
			enc3 = enc4 = 64;
		}
		*pszEncrypt++ = szKey[enc1]; *pszEncrypt++ = szKey[enc2];
		*pszEncrypt++ = szKey[enc3]; *pszEncrypt++ = szKey[enc4];
	}
	*pszEncrypt = 0;
	return 1;
}

void main(){
	unsigned char * pszData = "c-base64-demo-1.c\n程序中书写着所见所闻所感，编译着心中的万水千山。";
	int nCount = strlen(pszData);
	int nCacheSize = (nCount + 2) / 3 * 4 + 1;
	unsigned char * pszEncrypt = malloc(nCacheSize);

	printf("c-base64-demo-1.c\n");
	DisplayHexString(pszData);
	printf("%s\n", pszData);

	// ZeroMemory
	for(int i = 0; i < nCacheSize; i++) pszEncrypt[i] = 0;

	Base64Encode(pszData, pszEncrypt);
	printf("%s\n", pszEncrypt);

	free(pszEncrypt);
}

/*
c-base64-demo-1.c
63 2D 62 61 73 65 36 34-2D 64 65 6D 6F 2D 31 2E c-base64-demo-1.
63 0A E7 A8 8B E5 BA 8F-E4 B8 AD E4 B9 A6 E5 86 c...............
99 E7 9D 80 E6 89 80 E8-A7 81 E6 89 80 E9 97 BB ................
E6 89 80 E6 84 9F EF BC-8C E7 BC 96 E8 AF 91 E7 ................
9D 80 E5 BF 83 E4 B8 AD-E7 9A 84 E4 B8 87 E6 B0 ................
B4 E5 8D 83 E5 B1 B1 E3-80 82                   ..........
c-base64-demo-1.c
程序中书写着所见所闻所感，编译着心中的万水千山。
Yy1iYXNlNjQtZGVtby0xLmMK56iL5bqP5Lit5Lmm5YaZ552A5omA6KeB5omA6Ze75omA5oSf77yM57yW6K+R552A5b+D5Lit55qE5LiH5rC05Y2D5bGx44CC
*/