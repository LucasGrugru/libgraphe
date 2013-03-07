/*
 * TypVoisins.c
 *
 *  Created on: 29 janv. 2013
 */

#include <stdlib.h>
#include "TypVoisins.h"


/*
* Fonction : creationVoisin
*
* Parametres : 	int numeroSommet
* 				int poids
* 				TypVoisins* suivant
*
*
* Retour : pointeur sur TypGraphe
*
* Description : Fonction creant un un voisin et retournant un pointeur sur le voisin cree
*
*/
TypVoisins* creationVoisin(int numeroSommet, int poids, TypVoisins* suivant){
	/*Creation et allocation du voisin*/
	TypVoisins* voisin = NULL;
	voisin = (TypVoisins*)malloc(sizeof(TypVoisins));
	if(voisin == NULL)
		return NULL;
	
	/*Affectation des valeurs pour le nouveau voisin*/
	voisin->voisinSuivant = suivant;
	voisin->voisin = numeroSommet;
	voisin->poidsVoisin = poids;
	return voisin;
}

/*
* Fonction : creationVoisinFactice
*
* Parametres :
*
* Retour : TypVoisins*
*
* Description : cree un voisin factice a mettre en bout de liste des voisins d'un sommet
*
*/
TypVoisins* creationVoisinFactice(){
	TypVoisins* voisinFactice = NULL;
	voisinFactice = (TypVoisins*)malloc(sizeof(TypVoisins));
	if(voisinFactice == NULL)
		return NULL;
	
	voisinFactice->voisin = -1;
	voisinFactice->voisinSuivant = NULL;
	return voisinFactice;		
}



