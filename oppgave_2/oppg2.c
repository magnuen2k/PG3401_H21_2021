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
                            byOutBuffer[i/2] = hexToAscii(byInBuffer[i], byInBuffer[i + 1]);
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

int hexToInt(char c) {
    if (c >= 97)
        c = c - 32;
    int first = c / 16 - 3;
    int second = c % 16;
    int result = first * 10 + second;
    if (result > 9) result--;
    return result;
}

int hexToAscii(char c, char d) {
    int high = hexToInt(c) * 16;
    int low = hexToInt(d);
    return high+low;
}

void printOccurrencesOfAZ(char *text) {

    printf("Forekomster per bokstav: \n");

    char szAlphabet[] = "abcdefghijklmnopqrstuwxyz";
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