/*
 * TypGraphe.c
 *
 *  Created on: 29 janv. 2013
 *      Author: lgruber
 */
#include "TypVoisins.h"
#include "TypGraphe.h"

TypVoisins* premierElement(int sommet, TypVoisins** listeAdjacences) {
	return listeAdjacences[sommet];
}


