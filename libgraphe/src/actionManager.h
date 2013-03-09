/*
 * actionManager.h
 *
 *  Created on: 29 janv. 2013
 */

#include "TypGraphe.h"

#define QUITTER 1
#define CREATION 2
#define IMPORT 3
#define AFFICHAGE 4
#define ADD_SOMMET 5
#define DELETE_SOMMET 6
#define ADD_ARRETE 7
#define DELETE_ARRETE 8
#define SAUVEGARDE 9

int actionManager(int c, TypGraphe** g, int* possibilite);
int acquisitionInteger(char* s);
char acquisitionReponseON(char* s);