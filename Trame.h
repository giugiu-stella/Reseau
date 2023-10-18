/**
 * @file Trame.h
 * @author Giuliani Macabre
 * @brief 
 * @version 0.1
 * @date 2021-10-27
 * 
 * @copyright Copyright (c) 2021
 * 
 * Definit la structure d'une trame comme une liste chainee d'octets, decodage hexa->dec
 * Fait les imports de bibliotheques necessaires aux autres fichiers
 */

#ifndef _TRAME_H_
#define _TRAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *lectureTrame(FILE *f); //lecture + traitements des erreurs
void afficherTrame(char *T); //affiche une (1) trame formatee wireshark

#endif