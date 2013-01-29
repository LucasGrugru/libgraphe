/*
 * TypGraphe.h
 *
 *  Created on: 29 janv. 2013
 *      Author: lgruber
 */

#include "TypVoisins.h"

#ifndef TYPGRAPHE_H_
#define TYPGRAPHE_H_

typedef struct TypGraphe TypGraphe;
struct TypGraphe {
	int nbMaxSommet;
	TypVoisins** listesAdjacences;
};

TypVoisins* premierElement(int sommet, TypVoisins** listeAdjacences);
TypVoisins* creationArete(int voisin, int poids, TypVoisins* suivant);
int insertionArete(TypVoisins* voisin, int sommet, TypVoisins** listeAdjacences);




#endif /* TYPGRAPHE_H_ */
