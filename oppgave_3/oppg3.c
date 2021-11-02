#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/oppg3.h"

static void printList (NODE *pThis);

int main(int argc, char *argv[]) {

    LISTHEAD *pListHead = malloc(sizeof(LISTHEAD));

    int iRc = OK;

    int input;

    char szBuffer[255] = {0};

    while(input != 6) {

        printf("Velg hva du vil utføre:\n\r");
        printf("#1. Legg til et element i listen\n\r");
        printf("#2. Angre (Slette siste elementet)\n\r");
        printf("#3. Slett elementer på navn\n\r");
        printf("#4. Total pris for varer lagt i listen\n\r");
        printf("#5. Se kvittering\n\r");
        printf("#6. Avslutte\n\r");

        input = getchar() - '0';

        while(getchar() != '\n');
        
        switch(input){
            case 1:
                printf("Legg til navn på vare: \r\n");
                fgets(szBuffer, 255, stdin);
                addToList(pListHead, szBuffer, 8, 200);
                break;
            case 2:
                printf("Angrer..\r\n");
                deleteLastNode(pListHead);
                break;
            case 3:
                printf("Navn på vare du vil fjerne: \r\n");
                fgets(szBuffer, 255, stdin);
                deleteNodeByName(pListHead, szBuffer);
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


    // Just to make sure list is correct in development
    printList(pListHead->pHead);


    return 0;
}

static void printList (NODE *pThis) {
    int i = 0;
    while (pThis != NULL) {
        printf ("%d: %s\n", ++i, pThis->szName);
        pThis = pThis->pNext;
    }
    printf ("\n");
}