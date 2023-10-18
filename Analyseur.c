/**
 * @file Analyseur.c
 * @author Giuliani Macabre
 * @brief 
 * @version 0.1
 * @date 2021-10-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string.h>
#include "Trame.h"
#include "Analyse.h"

int main(){
    FILE *res = fopen("Resultats_analyse.txt", "w"); //fichier resultat
    printf("Entrez le nom de la trace a analyser :\n");
    char nom_fichier[50] = "";
    fgets(nom_fichier, 50, stdin);
    nom_fichier[strlen(nom_fichier)-1] = '\0';
    FILE *trace = fopen(nom_fichier,"r");
    if (trace){
        //lecture de la trame
        char *trame = lectureTrame(trace);
        printf("%s\n", trame);
        //afficherTrame(trame);
        //analyse couche 2 : Ethernet
        int i = analyseEthernet(trame, res);
        //analyse couche 3 : IP
        if (i != 0){
            i = analyseIP(trame, i, res);
            //analyse couche 4 : UDP
            //analyse couche 7 : DNS et DHCP
        }
        free(trame);
        fclose(trace);
    }
    else {
        printf("Impossible d'ouvrir le fichier.\n");
    }
    fclose(res);
    return 0;
}