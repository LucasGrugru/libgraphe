/*
 * TypVoisins.h
 *
 *  Created on: 29 janv. 2013
 *      Author: lgruber
 */

#ifndef TYPVOISINS_H_
#define TYPVOISINS_H_

typedef struct TypVoisins TypVoisins;
struct TypVoisins {
	int voisin;
	int poidsVoisin;
	TypVoisins* voisinSuivant;
};



#endif /* TYPVOISINS_H_ */
