/*
 * TypGraphe.h
 *
 *  Created on: 29 janv. 2013
 */

#include "TypVoisins.h"

#ifndef TYPGRAPHE_H_
#define TYPGRAPHE_H_

typedef struct TypGraphe TypGraphe;
struct TypGraphe {
	int nbMaxSommet;
	TypVoisins** listesAdjacences;
};

TypGraphe* creationGraphe(int nbSommetMax);
int ajoutSommet(int sommet, TypGraphe* graphe); 
int suppressionSommet(int sommet, TypGraphe* graphe);
int insertionArrete(int sommetCourant, int sommetVoisin, int poidsVoisinSuivant, TypGraphe* graphe);
int suppressionArrete(int sommetCourant, int sommetVoisin, int poidsVoisinSuivant, TypGraphe* graphe);
int destructionGraphe(TypGraphe** g);
int affichageGraphe(TypGraphe* g);
int sauvegardeGraphe(char* repertoire, char* nomFichier, TypGraphe* g);


#endif /* TYPGRAPHE_H_ */
