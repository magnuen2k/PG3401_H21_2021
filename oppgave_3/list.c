#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/oppgave_3.h"

static NODE *createNode(char *szName, int iQuantity, float fPrice) {
    NODE *p = malloc(sizeof(NODE));
    if (p != NULL) {
        p->pNext = NULL;
        p->pPrev = NULL;
        p->iQuantity = iQuantity;
        p->szName = strdup(szName);
        p->fPrice = fPrice;
    }
    return p;
}

NODE *lookupNamePrice(LISTHEAD *pListHead, char *szName, float fPrice) {

    NODE *pThis = pListHead->pHead;

    while(pThis) {

        if (pThis->fPrice == fPrice && strcasecmp(pThis->szName, szName) == 0) {
            break;
        }

        pThis = pThis->pNext;
    }

    return pThis;
}

int addToList(LISTHEAD *pListHead, char *szName, int iQuantity, float fPrice) {
    int iRc = ERROR;

    // Check if node already exists in list with same price
    NODE *pThis = lookupNamePrice(pListHead, szName, fPrice);

    if(pThis == NULL) {

        // Create new node
        pThis = createNode(szName, iQuantity, fPrice);

        // Add new node to list
        if (pThis != NULL) {

            if (pListHead->pHead == NULL) {
                pListHead->pHead = pThis;
                pListHead->pTail = pThis;
                iRc = OK;
            }
            else {
                pThis->pPrev = pListHead->pTail;
                pListHead->pTail->pNext = pThis;
                pListHead->pTail = pThis;

                iRc = OK;
            }
        }
    } else {
        // Increment quantity if node with same price already in list
        pThis->iQuantity += iQuantity;
        iRc = OK;
    }
    

    return iRc;
}

void deleteNode(LISTHEAD *pListHead, NODE *pNode) {
    
    if(pNode->pNext != NULL) {
        pNode->pNext->pPrev = pNode->pPrev;
    }

    if(pNode->pPrev != NULL) {
        pNode->pPrev->pNext = pNode->pNext;
    }

    if(pNode == pListHead->pHead) {
        pListHead->pHead = pNode->pNext;
    }

    if(pNode == pListHead->pTail) {
        pListHead->pTail = pNode->pPrev;
    }

    if(pNode->szName != NULL) {
        free(pNode->szName);
    }

    free(pNode);

}

int deleteLastNode(LISTHEAD *pListHead) {
    int iRc = ERROR;

    if(pListHead->pTail != NULL) {
        deleteNode(pListHead, pListHead->pTail);
        iRc = OK;
    }

    return iRc;
}

int deleteNodeByName(LISTHEAD *pListHead, char *szName) {
    int iRc = ERROR;

    NODE *p = pListHead->pHead;
    while(p != NULL) {
        NODE *pTmp = p;
        p = pTmp->pNext;
        if(strcasecmp(pTmp->szName, szName) == 0) {
            deleteNode(pListHead, pTmp);
        }
        iRc = OK;
    }

    return iRc;
}

float sumOfGoods(LISTHEAD *pListHead) {
    
    NODE *p = pListHead->pHead;
    float sum = 0;

    while(p != NULL) {
        sum += p->fPrice * p->iQuantity;
        p = p->pNext;
    }

    return sum;
}

void printReceipt(LISTHEAD *pListHead) {
    printf("------------------------------------ \n");
    printf("Kvittering på varer: \n");
    int i = 0;
    NODE *p = pListHead->pHead;
    while (p != NULL) {
        printf ("%d: Navn: %s\n", ++i, p->szName);
        printf ("%d: Antall: %d\n", i, p->iQuantity);
        printf ("%d: Pris per vare: %.2f\n", i, p->fPrice);
        p = p->pNext;
    }
    printf("Total sum: %.2f \n", sumOfGoods(pListHead));
    printf("------------------------------------ \n");
}

