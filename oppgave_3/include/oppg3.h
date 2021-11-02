#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define OK      0
#define ERROR   1

typedef struct _NODE {
    struct _NODE *pNext;
    struct _NODE *pPrev;
    char *szName;
    int iQuantity;
    float fPrice;

} NODE;

typedef struct _LISTHEAD {
   NODE *pHead;
   NODE *pTail;
} LISTHEAD;

int addToList(LISTHEAD *pListHead, char *szName, int iQuantity, float fPrice);
int deleteLastNode(LISTHEAD *pListHead);
int deleteNodeByName(LISTHEAD *pListHead, char *szName);
float sumOfGoods(LISTHEAD *pListHead);
void printReceipt(LISTHEAD *pListHead);

#endif // ndef _LINKEDLIST_H_