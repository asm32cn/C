// c-display-hex-string.c
#include <stdio.h>

const unsigned char szHexDigit[] = "0123456789ABCDEF";

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
	char szData[] = "“Life is like a box of chocolates：you never know what you＇re gonna get.”"
		"Tom Hanks，“Forrest Gump” \n----“生活就像一盒巧克力：你永远不知道你会得到什么。";

	printf(szData);
	printf("\n");
	DisplayHexString(szData);
}

/*
“Life is like a box of chocolates：you never know what you＇re gonna get.”Tom Hanks，“Forrest Gump”
----“生活就像一盒巧克力：你永远不知道你会得到什么。
E2 80 9C 4C 69 66 65 20-69 73 20 6C 69 6B 65 20 ...Life is like
61 20 62 6F 78 20 6F 66-20 63 68 6F 63 6F 6C 61 a box of chocola
74 65 73 EF BC 9A 79 6F-75 20 6E 65 76 65 72 20 tes...you never
6B 6E 6F 77 20 77 68 61-74 20 79 6F 75 EF BC 87 know what you...
72 65 20 67 6F 6E 6E 61-20 67 65 74 2E E2 80 9D re gonna get....
54 6F 6D 20 48 61 6E 6B-73 EF BC 8C E2 80 9C 46 Tom Hanks......F
6F 72 72 65 73 74 20 47-75 6D 70 E2 80 9D 20 0A orrest Gump... .
2D 2D 2D 2D E2 80 9C E7-94 9F E6 B4 BB E5 B0 B1 ----............
E5 83 8F E4 B8 80 E7 9B-92 E5 B7 A7 E5 85 8B E5 ................
8A 9B EF BC 9A E4 BD A0-E6 B0 B8 E8 BF 9C E4 B8 ................
8D E7 9F A5 E9 81 93 E4-BD A0 E4 BC 9A E5 BE 97 ................
E5 88 B0 E4 BB 80 E4 B9-88 E3 80 82             ............
*/