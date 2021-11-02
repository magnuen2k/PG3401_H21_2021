#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/oppg3.h"

static NODE *createNode(char *szName, int iQuantity, float fPrice) {
    NODE *p = malloc(sizeof(NODE));
    if (p != NULL) {
        p->iQuantity = iQuantity;
        p->szName = strdup(szName);
        //strcpy(p->szName, szName);
        //memcpy(p->szName, szName, sizeof(szName));
        p->fPrice = fPrice;
    }
    return p;
}

int addToList(LISTHEAD *pListHead, char *szName, int iQuantity, float fPrice) {
    int iRc = ERROR;
    NODE *pThis = createNode(szName, iQuantity, fPrice);

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
        NODE *pTmp = p;
        if(strncmp(p->szName, szName, sizeof(szName)) == 0) {
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
        p = pTmp->pNext;
        iRc = OK;
    }

    return iRc;
}

float sumOfGoods(LISTHEAD *pListHead) {
    
    NODE *p = pListHead->pHead;
    float sum = 0;
    int i = 1;

    while(p != NULL) {
        sum += p->fPrice * p->iQuantity;
        p = p->pNext;
    }

    return sum;
}

void printReceipt(LISTHEAD *pListHead) {
    printf("HER ER KVITTERING FORMATERT PENT");
}