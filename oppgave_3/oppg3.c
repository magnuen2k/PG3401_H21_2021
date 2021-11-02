#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/oppg3.h"

static void printList (NODE *pThis);
int getStringFromUser(char *szBuffer, int iSize);
int getIntFromUser(int *piBuffer);
int getFloatFromUser(float *pfBuffer);

int main(int argc, char *argv[]) {

    LISTHEAD *pListHead = malloc(sizeof(LISTHEAD));

    int input;

    char szBuffer[255] = {0};
    int iQuantity;
    float fPrice;

    while(input != 6) {

        printf("Velg hva du vil utføre:\n\r");
        printf("#1. Legg til et element i listen\n\r");
        printf("#2. Angre (Slette siste elementet)\n\r");
        printf("#3. Slett elementer på navn\n\r");
        printf("#4. Total pris for varer lagt i listen\n\r");
        printf("#5. Se kvittering\n\r");
        printf("#6. Avslutte\n\r");

        printList(pListHead->pHead);

        input = getchar() - '0';

        while(getchar() != '\n');
        
        switch(input){
            case 1:
                printf("Legg til navn på vare: \r\n");
                if(getStringFromUser(szBuffer, sizeof(szBuffer)) == OK && getIntFromUser(&iQuantity) == OK && getFloatFromUser(&fPrice) == OK) {
                    addToList(pListHead, szBuffer, iQuantity, fPrice);
                } else {
                    printf("Registrering avbrutt! \n");
                }
                break;
            case 2:
                printf("Angrer..\r\n");
                deleteLastNode(pListHead);
                break;
            case 3:
                printf("Navn på vare du vil fjerne: \r\n");
                if(getStringFromUser(szBuffer, sizeof(szBuffer)) == OK) {
                    deleteNodeByName(pListHead, szBuffer);
                }
                break;
            case 4:
                printf("Total sum for varer i listen: \r\n");
                printf("%f,- \n", sumOfGoods(pListHead));
                break;
            case 5:
                printf("Her er kvittering:\r\n");
                printReceipt(pListHead);
                break;  
            case 6:
                printf("Avslutter...\r\n");
                break;  
            default:
                printf("Trykket du feil?\n");
                break;
        }

    }

    while(pListHead->pHead) {
        deleteNode(pListHead, pListHead->pHead);
    }

    free(pListHead);

    return 0;
}

int getStringFromUser(char *szBuffer, int iSize) {
    if(fgets(szBuffer, iSize, stdin) != NULL) {
        szBuffer[strlen(szBuffer) - 1] = 0;
        if(strlen(szBuffer) > 0) {
            return OK;
        }
    }

    return ERROR;
}

int getIntFromUser(int *piBuffer) {
    char szBuffer[10] = {0};
    int iRc = getStringFromUser(szBuffer, sizeof(szBuffer));
    
    if(iRc == OK) {
        *piBuffer = atoi(szBuffer);
        return OK;
    }

    return iRc;
}

int getFloatFromUser(float *pfBuffer) {
    char szBuffer[10] = {0};
    int iRc = getStringFromUser(szBuffer, sizeof(szBuffer));
    
    if(iRc == OK) {
        *pfBuffer = atof(szBuffer);
        return OK;
    }

    return iRc;
}

static void printList (NODE *pThis) {
    int i = 0;
    while (pThis != NULL) {
        printf ("%d: %s\n", ++i, pThis->szName);
        pThis = pThis->pNext;
    }
}