/*
 * TypGraphe.h
 *
 *  Created on: 29 janv. 2013
 */

#include "TypVoisins.h"

#ifndef TYPGRAPHE_H_
#define TYPGRAPHE_H_

#define SUCCESS_CREATE_GRAPHE 1
#define SUCCESS_IMPORT_GRAPHE 2
#define SUCCESS_DELETE_ARRETE 3
#define SUCCESS_DELETE_SOMMET 4
#define SUCCESS_INSERTION_ARRETE 5
#define SUCCESS_ADD_SOMMET 6
#define SUCCESS_SAVE 7
#define SUCCESS_PRINT_SCREEN 8
#define SUCCESS_DELETE_GRAPHE 9
#define ERROR_CREATE_GRAPHE -1
#define ERROR_OPEN_FILE -2
#define ERROR_NOT_GRAPHE -3
#define ERROR_SOMMET_OUT_OF_RANGE -4
#define ERROR_EXISTING_SOMMET -5
#define ERROR_CREATE_SOMMET -6
#define ERROR_BAD_SOMMET -7
#define ERROR_BAD_VOISIN -8
#define ERROR_NOT_EXISTING_ARRETE -9
#define ERROR_EXISTING_ARRETE -10
#define ERROR_DELETE_ARRETE -11
#define ERROR_NOT_EXISTING_SOMMET -12

typedef struct TypGraphe TypGraphe;
struct TypGraphe {
	int nbMaxSommet;
	TypVoisins** listesAdjacences;
};

void messageManager(int err);
int creationGraphe(int nbMaxSommet,TypGraphe** graphe);
int importGraphe(char* pathFile, TypGraphe** graphe);
int ajoutSommet(int sommet, TypGraphe* graphe); 
int suppressionSommet(int sommet, TypGraphe* graphe);
int insertionArrete(int sommetCourant, int sommetVoisin, int poidsVoisinSuivant, TypGraphe* graphe);
int suppressionArrete(int sommetCourant, int sommetVoisin, int poidsVoisinSuivant, TypGraphe* graphe);
int destructionGraphe(TypGraphe** g);
int affichageGraphe(TypGraphe* g);
int sauvegardeGraphe(char* repertoire, char* nomFichier, TypGraphe* g);


#endif /* TYPGRAPHE_H_ */
