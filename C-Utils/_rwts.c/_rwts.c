// _rwts.c
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys\stat.h>

#define MAX_PATH 260

void main(int argc, char * args[]){
    struct stat sb;
    struct tm * _tm;
    char szNewFile[MAX_PATH];
    char * pszSource;
    char * pszFind1 = NULL, * pszFind2 = NULL;
    char * pszData;
    int n;

    for(int i = 1; i < argc; i++){
        pszSource = args[i];
        memset(szNewFile, 0, MAX_PATH);
        // printf("%d\t%s\n", i, pszSource);
        stat(pszSource, &sb);
        // printf("%lu\n", sb.st_mtime);
        // printf("st_mode=%d\n", S_ISDIR(sb.st_mode));
        _tm = localtime(&(sb.st_mtime));
        n = 0;
        if(! S_ISDIR(sb.st_mode) ){
            pszFind1 = strrchr(pszSource, '\\');
            pszFind2 = strrchr(pszSource, '.');

            // printf("%s\n", pszFind1);
            // printf("%s\n", pszFind2);
            if(pszFind2 && pszFind2 > pszFind1){
                n = pszFind2 - pszSource;
            }
        }

        if(n){
            strncpy(szNewFile, pszSource, n);
        }else{
            strcpy(szNewFile, pszSource);
        }

        if(n){
            pszData = szNewFile + n;
        }else{
            pszData = szNewFile + strlen(pszSource);
        }
        sprintf(pszData, "_(%d%02d%02d-%02d%02d%02d)",
            _tm->tm_year + 1900, _tm->tm_mon + 1, _tm->tm_mday,
            _tm->tm_hour, _tm->tm_min, _tm->tm_sec
        );

        if(n){
            pszData += 18;
            strcat(pszData, pszFind2);
        }

        printf("%s\n", pszSource);
        printf("%s\n", szNewFile);
        if( rename(pszSource, szNewFile) == 0 ){
            printf("True\n");
        }

        // printf("NF=%s\n", szNewFile);
    }
}