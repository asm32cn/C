// _base64_120chars.c
#include <io.h>
#include <stdio.h>

const unsigned char szKey[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

int nCount = 0;
void disp_char(unsigned char ch) {
	if (nCount > 0 && nCount % 120 == 0) {
		printf("\n");
	}
	printf("%c", ch);
	nCount++;
}

int file_to_base64(char * pszFileName) {
	// printf(pszFileName);
	if (_access(pszFileName, 0) != 0) {
		printf("Error: file not exists.");
		return -2;
	}

	FILE *fp;
	if ((fp = fopen(pszFileName, "rb")) == NULL) {
		printf("Error: fail to open file.");
		return -3;
	}

	int chr1 = 0, chr2 = 0, chr3 = 0;
	int enc1 = 0, enc2 = 0, enc3 = 0, enc4 = 0;
	while ((chr1 = fgetc(fp)) != EOF) {
		enc1 = chr1 >> 2;
		chr2 = fgetc(fp);
		if (chr2 == EOF) {
			enc2 = (chr1 & 3) << 4;
			enc3 = enc4 = 64;
		} else {
			enc2 = ((chr1 & 3) << 4) | ((chr2 & 0xf0) >> 4);
			chr3 = fgetc(fp);
			if (chr3 == EOF) {
				enc3 = (chr2 & 15) << 2;
				enc4 = 64;
			} else {
				enc3 = ((chr2 & 15) << 2) | ((chr3 & 0xc0) >> 6);
				enc4 = chr3 & 63;
			}
		}
		disp_char(szKey[enc1]); disp_char(szKey[enc2]);
		disp_char(szKey[enc3]); disp_char(szKey[enc4]);
	}
	fclose(fp);
	return 0;
}

int main(int argc, char ** argv) {

	if (argc != 2) {
		printf("Usage: %s [Filename]", argv[0]);
		return -1;
	}

	file_to_base64(argv[1]);

	return 0;
}