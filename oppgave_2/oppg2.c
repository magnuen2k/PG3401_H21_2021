#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./include/oppg2.h"

int main(int argc, char *argv[]) {

    FILE *f = NULL, *ft;
    unsigned char *byInBuffer = NULL;
    unsigned char *byOutBuffer = NULL;
    long lSize = 0, lBytesRead;

    f = fopen ("data.dta", "r");
    if (f != NULL) {
        if (fseek(f, 0, SEEK_END) == 0) {
            lSize = ftell(f);
            lSize -= lSize % 2;
            rewind(f);

            byInBuffer = malloc(lSize);
            byOutBuffer = malloc(lSize / 2 + 1);
            byOutBuffer[lSize / 2] = 0;

            if (byInBuffer != NULL) {
                ft = fopen("text.txt", "w");
                if(ft != NULL) {
                    lBytesRead = fread (byInBuffer, sizeof(unsigned char), lSize, f);
                    if (lBytesRead == lSize) {
                        int i;
                        for (i = 0; i < lSize; i+=2){
                            byOutBuffer[i/2] = hexToInt(byInBuffer[i], byInBuffer[i + 1]);
                        }
                        fprintf(ft, "%s", byOutBuffer);
                        printOccurrencesOfAZ(byOutBuffer);
                    }
                }
                free (byInBuffer);
                fclose(ft);
            }
        }
        fclose (f);
    }

	return 0;

}

int hexCharToInt(char c) {
    int iVal = c;
    
    if (iVal < 58) {
        iVal -= 48;     // 0-9 == 48-57 
    } else if (iVal < 97) {
        iVal -= 55;     // A-F == 65-70
    } else {
        iVal -= 87;     // a-f == 97-102
    }

    return (iVal >= 0 && iVal <= 15) ? iVal : 0;
}

int hexToInt(char c, char d) {
    return (hexCharToInt(c) << 4) + hexCharToInt(d);
}

void printOccurrencesOfAZ(char *text) {

    printf("Forekomster per bokstav: \n");

    char szAlphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char *szInput;

    int i;

    for(i = 0; i < strlen(szAlphabet); i++) {

        int count = 0;

        for(szInput = text; *szInput != 0; szInput++) {
            if (tolower(*szInput) == szAlphabet[i]) {
                count++;
            }
        }

        printf("%c: %d \n", szAlphabet[i], count);
    }
}