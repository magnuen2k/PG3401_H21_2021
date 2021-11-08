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
} MYHTTP;

MYHTTP* ProcessHttpHeader(char *pszHttp) {
    
    char* pszPtr;

    MYHTTP* pHttp = (MYHTTP*)malloc(sizeof(MYHTTP));
    
    if (!pHttp) return NULL;
    
    memset(pHttp, 0, sizeof(MYHTTP));
    pHttp->iHttpCode = atoi(pszHttp + strlen("HTTP/1.x "));
    
    // = wrong
    if (pHttp->iHttpCode == 200) {
        pHttp->bIsSuccess = true;
    }
    
    pszPtr = strstr(pszHttp, "Server");

    // Need space for zero termination (ref 7 not 6)
    // Allocate correct space to szServer
    if (pszPtr) {
        pszPtr += 6; while (!isalpha(pszPtr[0]))pszPtr++;

        strchr(pszPtr, '\n')[0] = 0;

        strcpy(pHttp->szServer, pszPtr);

        pszPtr[strlen(pHttp->szServer)] = '\n';

    }
    
    pszPtr = strstr(pszHttp, "Content-Type");
    
    // Allocate correct space to szContentType
    if (pszPtr) {
        pszPtr += 12; while (!isalpha(pszPtr[0]))pszPtr++;
        strchr(pszPtr, '\n')[0] = 0;

        strncpy(pHttp->szContentType, pszPtr, 15);
        pszPtr[strlen(pHttp->szContentType)] = '\n';
    }
    
    pszPtr = strstr(pszHttp, "Content-Length");
    
    if (pszPtr) {
        pszPtr += 14; while (!isdigit(pszPtr[0])) pszPtr++;
        pHttp->iContentLength = atoi(pszPtr);
    }

    return pHttp;
}

int main(int argc, char *argv[]) {

    char pszResponse[] = "HTTP/1.1 200 OK \r\nServer: Apache/2.4.1\r\nContent-Type: text/html\r\nContent-Length: 69\r\n\n";

    MYHTTP *httpResponse = ProcessHttpHeader(pszResponse);

    printf("%d \n", httpResponse->iHttpCode);
    printf("%s \n", httpResponse->szServer);
    printf("%s \n", httpResponse->szContentType);
    printf("%d \n", httpResponse->iContentLength);

    free(httpResponse);

    return 0;
}