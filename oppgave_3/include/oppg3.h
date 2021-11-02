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

int addToList(LISTHEAD *pListHead, char *pvName, int pvAge, char *pvMunicipality, int iSze);
//NODE *getElement(LISTHEAD *pListHead, int n);
//int getElementByName(LISTHEAD *pListHead, char *szName);
//void deleteByName(LISTHEAD *pListHead, char *szName);

#endif // ndef _LINKEDLIST_H_