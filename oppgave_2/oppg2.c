#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    FILE *f = NULL;
    unsigned char *byBuffer = NULL;
    long lSize = 0, lBytesRead;

    f = fopen ("data.dta", "r"); // Binary read. "r" for text would work too.
    if (f != NULL) {
        if (fseek(f, 0, SEEK_END) == 0) {
            lSize = ftell(f);
            printf ("Size of file is %ld bytes.\n", lSize);
            rewind(f);

            byBuffer = malloc (lSize);
            if (byBuffer != NULL) {
                lBytesRead = fread (byBuffer, sizeof(unsigned char), lSize, f);
                if (lBytesRead == lSize) {
                    // We got it all:
                    //printf("Buffer: %s", byBuffer);
                    int length = strlen(byBuffer);
                    int i;
                    char buf = 0;
                    for(i = 0; i < length; i++){
                        if(i % 2 != 0){
                            printf("%c", hex_to_ascii(buf, byBuffer[i]));
                        } else{
                            buf = byBuffer[i];
                        }
                    }
                }
                free (byBuffer);
            }
        }
        fclose (f);
    }

	return 0;

}