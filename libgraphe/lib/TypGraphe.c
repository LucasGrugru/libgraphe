/*
 * TypGraphe.c
 *
 *  Created on: 29 janv. 2013
 *      Author: lgruber
 */
#include "TypVoisins.h"
#include "TypGraphe.h"

TypGraphe* creationGraphe(int nbMaxSommet) {
	TypGraphe* t;
	t = (TypGraphe*)malloc(sizeof(TypGraphe));

	TypVoisins** listeAdjacences;
	listeAdjacences* = (TypVoisins**) malloc(sizeof(TypVoisins*));

	int i;
	for(i=0; i<nbMaxSommet; i++) {
		listeAdjacences[i] = NULL;
	}

	t.nbMaxSommet = nbMaxSommet;
	t.listeAdjacences = listeAdjacences;

	return t;
}

TypVoisins* premierElement(int sommet, TypVoisins** listeAdjacences) {
	if(listeAdjacences != NULL && listeAdjacences[sommet] != NULL)
		return listeAdjacences[sommet];
	else
		return NULL;
}

int insertionArete(int sommetCourant, int poids, TypVoisins** listeAdjacences) {
	TypVoisins* suivant = NULL;
	if(listeAdjacences != NULL && listeAdjacences[sommet] != NULL) {
		suivant = (TypVoisins*)malloc(sizeof(TypVoisins));
		TypVoisins* temp = listeAdjacences[sommetCourant];
		suivant.voisinSuivant = temp;
		suivant.poidsVoisin = poids;
		listeAdjacences[sommetCourant] = suivant;
		return 1;
	} else
		return -1;
}







