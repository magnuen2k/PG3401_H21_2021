#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _MYHTTP { 
    int iHttpCode; 
    int iContentLength;
    bool bIsSuccess; 
    char szServer[16]; 
    char szContentType[16];
    int iYearModified;
} MYHTTP;

MYHTTP* ProcessHttpHeader(char *pszHttp) {
    
    char* pszPtr;

    MYHTTP* pHttp = (MYHTTP*)malloc(sizeof(MYHTTP));
    
    if (!pHttp) return NULL;
    
    memset(pHttp, 0, sizeof(MYHTTP));
    pHttp->iHttpCode = atoi(pszHttp + strlen("HTTP/1.x "));
    
    if (pHttp->iHttpCode == 200) {
        pHttp->bIsSuccess = true;
    }
    
    pszPtr = strstr(pszHttp, "Server");

    if (pszPtr) {
        pszPtr += 6; 
        while (!isalpha(pszPtr[0])){
            pszPtr++;
        }

        strchr(pszPtr, '\n')[0] = 0;

        strncpy(pHttp->szServer, pszPtr, 16);
        pHttp->szServer[15] = 0;
        
        pszPtr[strlen(pszPtr)] = '\n';

    }
    
    pszPtr = strstr(pszHttp, "Content-Type");
    
    if (pszPtr) {
        pszPtr += 12; 
        while (!isalpha(pszPtr[0])){
            pszPtr++;
        }

        strchr(pszPtr, '\n')[0] = 0;

        strncpy(pHttp->szContentType, pszPtr, 16);
        pHttp->szContentType[15] = 0;
        pszPtr[strlen(pszPtr)] = '\n';
    }
    
    pszPtr = strstr(pszHttp, "Content-Length");
    
    if (pszPtr) {
        pszPtr += 14; 
        while (!isdigit(pszPtr[0])) {
            pszPtr++;
        }
        pHttp->iContentLength = atoi(pszPtr);
    }

    pszPtr = strstr(pszHttp, "Last-Modified");

    if (pszPtr) {
        pszPtr += 13; 
        while (!isalpha(pszPtr[0])) {
            pszPtr++;
        }

        // Documentation states that year, month, and date are fixed sized numbers.
        pszPtr += 12;

        pHttp->iYearModified = atoi(pszPtr);

        pszPtr[strlen(pszPtr)] = '\n';
    }

    return pHttp;
}

int main(int argc, char *argv[]) {

    char pszResponse[] = "HTTP/1.1 200\nServer: Apache/2.4.1\nContent-Type: text/html\nContent-Length: 432\nLast-Modified: Wed, 10 Oct 2021 19:10:00 GMT\n";

    MYHTTP *httpResponse = ProcessHttpHeader(pszResponse);

    printf("Status code: %d \n", httpResponse->iHttpCode);
    printf("Server: %s \n", httpResponse->szServer);
    printf("Content-Type: %s \n", httpResponse->szContentType);
    printf("Content-Length: %d \n", httpResponse->iContentLength);
    printf("Year modified: %d \n", httpResponse->iYearModified);

    free(httpResponse);

    return 0;
}