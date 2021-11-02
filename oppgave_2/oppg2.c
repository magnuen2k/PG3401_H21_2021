#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printOccurrencesOfAZ(char *text);

int hex_to_int(char c){
    if (c >= 97)
        c = c - 32;
    int first = c / 16 - 3;
    int second = c % 16;
    int result = first * 10 + second;
    if (result > 9) result--;
    return result;
}

int hex_to_ascii(char c, char d){
    int high = hex_to_int(c) * 16;
    int low = hex_to_int(d);
    return high+low;
}

int main(int argc, char *argv[]) {

    FILE *f = NULL, *ft;
    unsigned char *byBuffer = NULL;
    long lSize = 0, lBytesRead;

    f = fopen ("data.dta", "r");
    if (f != NULL) {
        if (fseek(f, 0, SEEK_END) == 0) {
            lSize = ftell(f);
            printf ("Size of file is %ld bytes.\n", lSize);
            rewind(f);

            byBuffer = malloc (lSize);
            if (byBuffer != NULL) {
                ft = fopen("text.txt", "w");
                if(ft != NULL) {
                    lBytesRead = fread (byBuffer, sizeof(unsigned char), lSize, f);
                    if (lBytesRead == lSize) {
                        int i;
                        char buf = 0;
                        for(i = 0; i < strlen(byBuffer); i++){
                            if(i % 2 != 0){
                                fprintf(ft, "%c", hex_to_ascii(buf, byBuffer[i]));
                            } else{
                                buf = byBuffer[i];
                            }
                        }
                        printOccurrencesOfAZ(byBuffer);
                    }
                }
                free (byBuffer);
                fclose(ft);
            }
        }
        fclose (f);
    }

	return 0;

}

void printOccurrencesOfAZ(char *text) {
    printf("%s", text);
}