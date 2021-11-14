#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#include "./include/oppgave_6.h"

#ifdef __linux__
#include <linux/in.h>
#endif

#define READBUFFERSIZE 10

int main(int argc, char *argv[]) {

    int sockFd;
    char *pszResponseBuffer = NULL;
    char *pszRequest = "GET /pg3401/test.html HTTP/1.1\r\nHost: www.eastwillsecurity.com\r\nContent-Type: text/html\r\n\r\n";
    
    sockFd = connectToSocket("77.111.240.75", 80);

    if(sockFd != -1 && sendToSocket(sockFd, pszRequest) >= 0) {
        
        // Get the allocated buffer for whats sent over the socket
        pszResponseBuffer = getResponse(sockFd);
        
        printPage(pszResponseBuffer);

        free(pszResponseBuffer);
    }

    if (sockFd != -1) {
        close(sockFd);
        sockFd = -1;
    }

    return 0;
}

void printPage(char *pszResponseBuffer) {

    char *pszHeadBuffer = strdup(pszResponseBuffer);

    // If strdup fail, print the full response
    if (pszHeadBuffer == NULL) {
        printf("%s", pszResponseBuffer);
    } else {
        // Get the content length
        char *pszContentLength = strstr(pszHeadBuffer, "Content-Length:");
        pszContentLength += 16;
        char *pszEol = pszContentLength;
        while (isdigit(*pszEol)) {
            pszEol++;
        }
        *pszEol = 0;
        int iContentLength = atoi(pszContentLength);

        // Print the last part of the full response
        printf("%s", &pszResponseBuffer[strlen(pszResponseBuffer) - iContentLength]);
        free(pszHeadBuffer);
    }
}

char* getResponse(int sockFd) {

    char szReadBuffer[READBUFFERSIZE];
    char *pszResponseBuffer = NULL;
    int iResponseLength = 0;

    while((iResponseLength = recv(sockFd, szReadBuffer, sizeof(szReadBuffer) -1, 0)) > 0) {
        szReadBuffer[iResponseLength] = 0;

        if(!pszResponseBuffer) {
            // Allocate the buffer first time we read the response
            pszResponseBuffer = malloc(iResponseLength + 1);
            strcpy(pszResponseBuffer, szReadBuffer);
        } else {
            // Reallocate and append the string we received
            pszResponseBuffer = realloc(pszResponseBuffer, strlen(pszResponseBuffer) + iResponseLength + 1);
            strcat(pszResponseBuffer, szReadBuffer);
        }
        
        // If we recieved less characters than we asked for, then we are done
        if (iResponseLength < (sizeof(szReadBuffer) - 1)) {
            break;
        }
    };

    return pszResponseBuffer;
}

int connectToSocket(char *pszNetAddr, int iPort) {
    struct sockaddr_in saAddr = {0};
    int sockFd;

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        printf("Socket failed with error code: %i \n", errno);
    } else {
        saAddr.sin_addr.s_addr = inet_addr(pszNetAddr);
        saAddr.sin_family = AF_INET;
        saAddr.sin_port = htons(iPort);

        if (connect(sockFd, (struct sockaddr *) &saAddr, sizeof(saAddr)) < 0) {
            printf("Connection failed with error code: %i\n", errno);
            close(sockFd);
            sockFd = -1;
        }
    }

    return sockFd;
}

int sendToSocket(int sockFd, char *pszRequest) {
    if (sockFd == -1) {
        return -1;
    }

    if (send(sockFd, pszRequest, strlen(pszRequest), 0) < 0) {
        printf("Failed to send request with error code: %i\n", errno);
        return -1;
    };

    return 0;
}