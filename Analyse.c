/**
 * @file Analyse.c
 * @author Giuliani Macabre
 * @brief 
 * @version 0.1
 * @date 2021-10-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Analyse.h"

/**
 * Toutes les fonctions d'analyse (sauf dns et dhcp) renvoient 
 * la position de l'octet a partir duquel l'analyse suivante 
 * doit commencer. Cette position sera ensuite mise en parametre
 * de la fonction d'analyse (sauf pour ethernet qui commence a la
 * position 0)
 * 
 */


/**
 * Destination sur 6 o
 * Source sur 6 o
 * Type sur 2 o
 */
int analyseEthernet(char *trame, FILE *f){
    char *dest = (char *)malloc(18*sizeof(char));
    strcpy(dest,"");
    char *src = (char *)malloc(18*sizeof(char)); 
    strcpy(src,"");
    char *type = (char *)malloc(30*sizeof(char)); 
    strcpy(type,"");
    char octet[2];
    octet[0] = trame[0];
    octet[1] = trame[1];
    strcat(dest, octet);
    int i=3;
    while (i<17){
        strcat(dest, ":");
        octet[0] = trame[i];
        octet[1] = trame[i+1];
        strcat(dest, octet);
        i+=3;
    }
    octet[0] = trame[i];
    octet[1] = trame[i+1];
    strcat(src, octet);
    i+=3;
    while (i<35){
        strcat(src, ":");
        octet[0] = trame[i];
        octet[1] = trame[i+1];
        strcat(src, octet);
        i+=3;
    }
    while (i<41){
        octet[0] = trame[i];
        octet[1] = trame[i+1];
        strcat(type, octet);
        i+=3;
    }
    //on peut faire l'analyse IP demandee que si le type est IPv4
    if (strcmp(type, "0800") == 0){ 
        strcat(type, " (IPv4)");
        return i;
    }
    if (strcmp(type, "86DD") == 0){ strcat(type, " (IPv6)");}
    if (strcmp(type, "0805") == 0){ strcat(type, " (X.25 niveau 3)");}
    if (strcmp(type, "0806") == 0){ strcat(type, " (ARP)");}
    if (strcmp(type, "8035") == 0){ strcat(type, " (RARP)");}
    if (strcmp(type, "8098") == 0){ strcat(type, " (Appletalk)");}
    if (strcmp(type, "88CD") == 0){ strcat(type, " (SERCOS III)");}
    if (strcmp(type, "0600") == 0){ strcat(type, " (XNS)");}
    if (strcmp(type, "8100") == 0){ strcat(type, " (VLAN)");}
    fprintf(f, "Champ Ethernet :\n\tAdresse MAC Destination : %s\n\tAdresse MAC Source : %s\n\tType : 0x%s\n", dest, src, type);
    free(dest);
    free(src);
    free(type);
    return 0;
}

/**
 * 20 o sans les options :
 *  version sur 4 bits
 *  IHL sur 4 bits
 *  TOS sur 1 o
 *  total length sur 2 o
 *  id sur 2 o
 *  flags sur 3 bits, fragment offset sur 13 bits
 *  TTL sur 1 o
 *  protocol sur 1 o
 *  header checksum sur 2 o
 *  src sur 4 o
 *  dest sur 4 o
 * 
 * options sur ?? o -> determine par IHL
 */
int analyseIP(char *trame, int i, FILE *f){
    char ver, ihl, tos[2], totalLen[4], id[4], flags[2], fragOffset[13], ttl[2], proto[2], checksum[4];
    char *src = (char *)malloc(16*sizeof(char));
    char *dest = (char *)malloc(16*sizeof(char));
    ver = trame[i];
    ihl = trame[i+1];
    tos[0] = trame[i+3]; //saut de l'espace
    tos[1] = trame[i+4];
    totalLen[0] = trame[i+6];
    totalLen[1] = trame[i+7];
    totalLen[2] = trame[i+9];
    totalLen[3] = trame[i+10];
    id[0] = trame[i+12];
    id[1] = trame[i+13];
    id[2] = trame[i+15];
    id[3] = trame[i+16];
    //flags+offset sur 2o
    ttl[0] = trame[i+21];
    ttl[1] = trame[i+22];
    proto[0] = trame[i+24];
    proto[1] = trame[i+25];
    checksum[0] = trame[i+27];
    checksum[1] = trame[i+28];
    checksum[2] = trame[i+30];
    checksum[3] = trame[i+31];

    //addr src & dest
    char *opt = (char *)malloc(40*sizeof(char));
    fprintf(f, "Champ IP :\n\tVersion : 0x%c\n\tIHL : 0x%c\n\tTOS : %s\n\tLongueur totale : 0x%s (%d octets)\n\tIdentification : 0x%s\n\tFlags : 0 | DF : %c | MF : %c\n\tFragment offset : 0x%s\n\tTTL : 0x%s\n\tProtocol : 0x%s\n\tHeader Checksum : 0x%s\n\tAdresse IP Source : %s\n\tAdresse IP Destination : %s\n\tOptions : %s", ver, ihl, tos, totalLen, id, flags[1], flags[2], fragOffset, ttl, proto, checksum, src, dest, opt);
}

int main(){
    FILE *res = fopen("Resultats_analyse.txt", "w");
    char trame[] = "ff ff ff ff ff ff 08 00 20 02 45 9e 08 06 00 01 08 00 06 04 00 01 08 00 20 02 45 9e 81 68 fe 06 00 00 00 00 00 00 81 68 fe 05 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00";
    int i = analyseEthernet(trame, res);
    //i = analyseIP(trame, i, res);
    fclose(res);
    return 0;
}