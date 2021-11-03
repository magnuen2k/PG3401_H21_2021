#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#ifdef __linux__
#include <linux/in.h>
#endif

int main(int argc, char *argv[]) {

    struct sockaddr_in saAddr = {0};
    int sockFd, iPort = atoi("80");
    char szReplyBuffer[1024];
    char *szRequest = "GET /pg3401/test.html HTTP/1.1\r\nHost: www.eastwillsecurity.com\r\nContent-Type: text/html\r\n\r\n";
    
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFd < 0) {
        printf("Socket failed with error code: %i \n", errno);
    }

    saAddr.sin_addr.s_addr = inet_addr("77.111.240.75");
    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);

    if(connect(sockFd, (struct sockaddr *) &saAddr, sizeof(saAddr)) < 0) {
        printf("Connection failed with error code: %i\n", errno);
    }

    if(send(sockFd, szRequest, strlen(szRequest), 0) < 0) {
        printf("Failed to send request with error code: %i\n", errno);
    };

    if(recv(sockFd, szReplyBuffer, 1024, 0) < 0) {
        printf("Failed to get response %i\n", errno);
    };

    printf("%s", szReplyBuffer);

    close(sockFd);
    sockFd = -1;

    return 0;
}