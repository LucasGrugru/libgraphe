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
TypGraphe* creationGraphe(int nbSommetMax);
TypVoisins* premierElement(int sommet, TypVoisins** listeAdjacences);
int insertionArete(int sommetCourant, int poids, TypVoisins** listeAdjacences);


#endif /* TYPGRAPHE_H_ */
