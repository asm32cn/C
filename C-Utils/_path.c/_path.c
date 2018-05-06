#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	char szLine[_MAX_PATH] = {0};

	char * env = getenv("path");
	char * pEnd = env;
	int i = 0;
	do{
		if(';' == (szLine[i] = *pEnd)){
			szLine[i] = '\n';
			szLine[i + 1] = 0;
			printf(szLine);
			i = 0;
		}else{
			i++;
		}
	}while(*pEnd++);
	szLine[i - 1] = '\n';
	szLine[i] = 0;
	printf(szLine);
	return 0;
}
