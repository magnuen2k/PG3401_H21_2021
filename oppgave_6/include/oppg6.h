#ifndef _SOCKET_H_
#define _SOCKET_H_

void printPage(char *pszResponseBuffer);
char* getResponse(int sockFd);
int connectToSocket(char *pszNetAddr, int iPort);
int sendToSocket(int sockFd, char *pszRequest);

#endif // ndef _SOCKET_H_