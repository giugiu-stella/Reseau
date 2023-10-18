/**
 * @file Analyse.h
 * @author Giuliani Macabre
 * @brief 
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _ANALYSE_H_
#define _ANALYSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int analyseEthernet(char *trame, FILE *f);
int analyseIP(char *trame, int i, FILE *f);
int analyseUDP(char *trame, int i, FILE *f);
void analyseDNS(char *trame, int i, FILE *f);
void analyseDHCP(char *trame, int i, FILE *f);

#endif