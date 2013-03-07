/*
 * main.c
 *
 *  Created on: 29 janv. 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TypVoisins.h"
#include "TypGraphe.h"
#include "actionManager.h"

int menu(int possibilite);

int main(int argv, char** argc) {
	TypGraphe* graphe = NULL;
	int possibilite = 0;
	while(1){
		int choix = menu(possibilite);
		actionManager(choix, &graphe, &possibilite);
	}
}

/*
* Fonction : menu
*
* Parametres :
*
*
* Retour : int
*
* Description : retourne la valeur de choix de l'utilisateur
*
*/
int menu(int possibilite) {
	int retour = 0;
	int choix;
	char* s = (char*)malloc(500*sizeof(char));
	strcpy(s, "");
	strcat(s, "\nChoix ?\n");
	strcat(s, "1 : Quitter l'application\n");
	strcat(s, "2 : Création d'un graphe manuellement\n");
	strcat(s, "3 : Import d'un graphe\n");
	/*Bloque les possiblite si le graphe n'existe pas*/
	if(possibilite == 1){
		strcat(s, "4 : Affichage d'un graphe\n");
		strcat(s, "5 : Ajout d'un sommet\n");
		strcat(s, "6 : Suppression d'un sommet\n");
		strcat(s, "7 : Ajout d'une arrete\n");
		strcat(s, "8 : Suppression d'une arrete\n");
		strcat(s, "9 : Sauvegarde du graphe courant\n\n");
	}
	choix = acquisitionInteger(s);
	free(s);
	return choix;
}
