/*
 * TypVoisins.h
 *
 *  Created on: 29 janv. 2013
 */

#ifndef TYPVOISINS_H_
#define TYPVOISINS_H_

typedef struct TypVoisins TypVoisins;
struct TypVoisins {
	int voisin;
	int poidsVoisin;
	TypVoisins* voisinSuivant;
};

TypVoisins* creationVoisin(int numeroSommet, int poids, TypVoisins* suivant);
TypVoisins* creationVoisinFactice();


#endif /* TYPVOISINS_H_ */
