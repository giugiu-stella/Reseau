#include "Trame.h"

//donne l'équivalent de la d'un caractere hexadécimal en int décimal
int valeurdec(char c){
    if(c=='0'){
        return 0;
    }
    if(c=='1'){
        return 1;
    }
    if(c=='2'){
        return 2;
    }
    if(c=='3'){
        return 3;
    }
    if(c=='4'){
        return 4;
    }
    if(c=='5'){
        return 5;
    }
    if(c=='6'){
        return 6;
    }
    if(c=='7'){
        return 7;
    }
    if(c=='8'){
        return 8;
    }
    if(c=='9'){
        return 9;
    }
    if(c=='A'){
        return 10;
    }
    if(c=='B'){
        return 11;
    }
    if(c=='C'){
        return 12;
    }
    if(c=='D'){
        return 13;
    }
    if(c=='E'){
        return 14;
    }
    if(c=='F'){
        return 15;
    }
    return -1;
}

//transformation de l'héxadécimal en décimal
int hex2dec(char hexa[], int taille){
    int i=taille-1;
    int resultat=0;
    int valeur=0;
    int puissance= 0;
    while(i>=0){
        valeur=valeurdec(hexa[i]);
        resultat= resultat+valeur*pow(16.0,puissance*1.0);
        i--;
        puissance ++; 
    }
    return resultat;
}

//renvoie 1 si l'offset est valide, 0 sinon
int offsetValide(char *offset, int offsetLen, char *charHexa){
    //offset doit faire au moins 3 octets de long (6 chiffres hexa)
    if (offsetLen >= 6){
        //offset doit etre en hexadecimal
        int j=0;
        while (j<strlen(offset)){
            if (!strchr(charHexa, offset[j])){
                return 0;
            }
            j++;
        }
        return 1;
    }
    return 0;
}

char *lectureTrame(FILE *f){
    char *t = (char *)malloc(10000*sizeof(char));
    strcpy(t, "");
    char buffer[200];
    int nbTrames = 0;
    while (fgets(buffer, 200, f)){
        /**
         * conditions pour lever une erreur et retourner 0:
         * - offset de la 1ere ligne != 0
         * - ligne incomplete (offset suivant plus grand que nb o de la ligne)
         * erreurs a ignorer:
         * - texte entre 2 lignes ou entre 2 trames
         * - octets en fin de ligne (offset suivant plus petit que nb o de la ligne)
         * - offset invalide (pas en hexa ou < 3 o)
         * 
         */
        int i=0;
        char offset[20];
        //1ere ligne
        sscanf(buffer, "%s", offset);
        if (hex2dec(offset, strlen(offset)) == 0){
            nbTrames++; //offset a 0 -> il s'agit d'une nouvelle trame
        }
        char *ligne = buffer+strlen(offset)+1;
        ligne[strlen(ligne)-2] = '\0';
        printf("%s\n", ligne);
        strcat(t, ligne);
    }
    
    return t;
}

void afficherTrame(char *T){
    printf("Voici la trame etudiee :\n");
    printf("%s\n", T);
    int offset = 0;
    int i=0;
    while (i<strlen(T)){
        printf("%04x ", offset);
        while ((i+1)%48 != 0 && i<strlen(T)){
            printf("%c", T[i]);
            i++;
        }
        printf("%c", T[i]);
        i++; //saut de l'espace
        printf("\n");
        offset+=16;
    }
}
