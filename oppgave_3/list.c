#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/oppg3.h"

static NODE *createNode(char *szName, int iQuantity, int iPrice)
{
    NODE *p = malloc(sizeof(NODE));
    if (p != NULL) {
        p->iQuantity = iQuantity;
        //p->szName = strdup(szName);
        strcpy(p->szName, szName);
        p->fPrice = iPrice;
    }
    return p;
}

int addToList(LISTHEAD *pListHead, char *szName, int iQuantity, int iPrice)
{
    int iRc = ERROR;
    NODE *pThis = createNode(szName, iQuantity, iPrice);

    if (pThis != NULL) {

        if (pListHead->pHead == NULL) {
            pListHead->pHead = pThis;
            pListHead->pTail = pThis;
            iRc = OK;
        }
        else {
            NODE *pTmp = pListHead->pTail;
            pTmp->pNext = pThis;
            pThis->pPrev = pTmp;
            pListHead->pTail = pThis;

            iRc = OK;
        }
    }

    return iRc;
}

int deleteLastNode(LISTHEAD *pListHead) {
    int iRc = ERROR;

    if(pListHead->pTail == NULL) {
        // empty
    } else {
        NODE *pTmp = pListHead->pTail;
        pTmp->pPrev->pNext = NULL;
        pListHead->pTail = pTmp->pPrev;
        free(pTmp);
        iRc = OK;
    }

    return iRc;

}

int deleteNodeByName(LISTHEAD *pListHead, char *szName) {
    int iRc = ERROR;

    NODE *p = pListHead->pHead;
    while(p != NULL) {
        if(strcmp(tolower(p->szName), tolower(szName)) == 0) {
            if (pListHead->pHead == p) {
                pListHead->pHead = p->pNext;
            } else if (pListHead->pTail == p) {
                NODE *pTmp = pListHead->pTail;
                pTmp->pPrev->pNext = NULL;
                pListHead->pTail = pTmp->pPrev;
            } else {
                p->pPrev->pNext = p->pNext;
                p->pNext->pPrev = p->pPrev;
            }
            free(p);
        }
        p = p->pNext;
        iRc = OK;
    }

    return iRc;

}