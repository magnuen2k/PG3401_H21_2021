#include <stdio.h>
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

    char *st = "446574746520657220656e2066696c206465726520736b616c207465737465206d65642c2064656e20696e6e65686f6c6465722074656b737420736f6d2065722068657820656e6b6f6465742e2044656e6e65206f7070676176656e20696c6c757374726572657220656e6b656c206c6573696e672061762066696c6572206f672061742064657265206b616e20746120656e20656e6b656c206b6f6e766572746572696e6720617620646174612c2073616d7420656e6b656c206c6f6f70206b6f64652e204465747465206b6c61726572206475206e6f6b2066696e742e";

	/*FILE *f;
	char c;
	f=fopen("data.dta","r");
	while((c=fgetc(f))!=EOF)
	{
		printf("%c",c);
	}
	fclose(f);*/

    int length = strlen(st);

    int i;
        char buf = 0;
        for(i = 0; i < length; i++){
            if(i % 2 != 0){
                printf("%c", hex_to_ascii(buf, st[i]));
            } else{
                buf = st[i];
            }
        }

	return 0;

}