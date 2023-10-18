#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

int main(){
    char trame[200] = "ff ff ff ff ff ff 08 00 20 02 45 9e 08 06 00 01";
    char addest[17];
    char octet[2];
    sscanf(trame, "%s", octet);
    //strcat(addest, octet);
    int i=1;
    while (i<14){
        //strcat(addest, ":");
        sscanf(trame, "%s", octet);
        //strcat(addest, octet);
        i++;
    }
    
    printf("%s\n", octet);
    return 0;
}