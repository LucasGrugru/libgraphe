/*
 * TypGraphe.c
 *
 *  Created on: 29 janv. 2013
 */
#include "TypVoisins.h"
#include "TypGraphe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
* Fonction : creationGraphe
*
* Parametres : int nbMaxSommet
*
*
* Retour : pointeur sur TypGraphe
*
* Description : Fonction creant un graphe de taille maximum nbMaxSommet
*
*/
TypGraphe* creationGraphe(int nbMaxSommet) {
	TypGraphe* t = NULL;
	int i;
	t = (TypGraphe*)malloc(sizeof(TypGraphe));
	if(t == NULL)
		return NULL;

	TypVoisins** listeAdjacences;
	listeAdjacences = (TypVoisins**) malloc(nbMaxSommet * sizeof(TypVoisins*));

	for(i=0; i<nbMaxSommet; i++) {
		listeAdjacences[i] = NULL;
	}

	t->nbMaxSommet = nbMaxSommet;
	t->listesAdjacences = listeAdjacences;
	printf("Graphe de %d sommets maximum crée\n\n", nbMaxSommet);
	return t;
}


/*
* Fonction : ajoutSommet
*
* Parametres : 	int sommet
* 				TypGraphe* graphe
*
* Retour : int
*
* Description : ajoute un sommet au graphe
*
*/
int ajoutSommet(int sommet, TypGraphe* graphe) {
	if(graphe == NULL || graphe->listesAdjacences == NULL){
			printf("Graphe inexistant\n");
			return -1;
	}
	if(sommet > graphe->nbMaxSommet){
		printf("Sommet choisi hors limite\n");
		return -2;
	}
	if(graphe->listesAdjacences[sommet] != NULL){
		printf("Sommet deja existant\n");
		return -3;
	}
	
	TypVoisins* voisinFactice = creationVoisinFactice();
	if(voisinFactice == NULL){
		printf("Erreur a la creation du sommet\n");
		return -4;
	}
	
	graphe->listesAdjacences[sommet] = voisinFactice;
}

/*
* Fonction : suppressionSommet
*
* Parametres : 	int sommet
* 				TypGraphe* graphe
*
* Retour : int
*
* Description : supprime un sommet au graphe
*
*/
int suppressionSommet(int sommet, TypGraphe* graphe){
	TypVoisins* temp;
	int i;
	
	suppressionArreteSommet(sommet, graphe);
	
	/*Recherche des voisins avec sommet comme voisin*/
	/*Parcours de chaque sommet potentiel du graphe*/
	for(i = 0; i < graphe->nbMaxSommet; i++){	
		temp = graphe->listesAdjacences[i];
		/*Parcrous de tous les voisins d'un sommet donne*/
		while(temp != NULL){
			/*Si le voisin est le sommet supprime, on supprime l'arrete correspondante*/
			if(temp->voisin == sommet){
				suppressionArrete(i, sommet, temp->poidsVoisin, graphe);
			}
			temp = temp->voisinSuivant;
			
		}
	}
	printf("Sommet %d supprime\n", sommet);
	return 1;
}

/*
* Fonction : arreteExistante
*
* Parametres : 	int sommetCourant
*				int poidsVoisinSuivant
*				int sommetVoisin
*				Pointeursur tableau de TypVoisins
*
* Retour : int
*
* Description : retourne 0 si l'arrete est inexistante, 1 si elle existe, -1 si erreur
*
*/
int arreteExistante(int sommetCourant, int sommetVoisin, int poidsVoisinSuivant, TypVoisins** listeAdjacences) {
	TypVoisins* temp = listeAdjacences[sommetCourant];
	/*tant que l'on a pas parcouru tous les voisins du sommetCourant*/
	while(temp->voisin != -1){
		/*Si il existe un voisin avec le numero sommetVoisin et ayant pour poids poidsVoisinSuivant*/
		if(temp->voisin == sommetVoisin &&
				temp->poidsVoisin == poidsVoisinSuivant)
			return 1;
		
		temp = temp->voisinSuivant;
	}
	return 0;
}

/*
* Fonction : insertionArrrete
*
* Parametres : 	int sommetCourant
*				int poidsVoisinSuivant
*				int sommetVoisin
*				Pointeursur tableau de TypVoisins
*
* Retour : entier
*
* Description : Insere une arrete entre le sommetCourant et le voisin de poids poidsVoisinSuivant
*
*/
int insertionArrete(int sommetCourant, int sommetVoisin, int poidsVoisinSuivant, TypGraphe* graphe) {
	TypVoisins* suivant = NULL;
	/*Si le graphe en entree n'existe pas*/
	if(graphe == NULL || graphe->listesAdjacences == NULL){
		printf("Graphe inexistant\n");
		return -1;
	}
	/*Si le sommet en entree n'est pas dans le graphe ou si il n'est pas encore cree*/
	if(sommetCourant >= graphe->nbMaxSommet || graphe->listesAdjacences[sommetCourant] == NULL){
		printf("Le sommet de depart choisi est incorrect\n");
		return -2;
	}
	/*Si le voisin en entree n'est pas dans le graphe ou si il n'est pas encore cree*/
	if(sommetVoisin >= graphe->nbMaxSommet || graphe->listesAdjacences[sommetVoisin] == NULL){
		printf("Le voisin choisi est incorrect\n");
		return -3;
	}
	/*Si l'arrete existe deja*/
	if(arreteExistante(sommetCourant, sommetVoisin, poidsVoisinSuivant, graphe->listesAdjacences)){
		printf("Arrete entre les sommets %d et %d de poids %d deja existante\n", sommetCourant, sommetVoisin, poidsVoisinSuivant);
		return -4;
	}
	
	/*Sauvegarde du pointeur du premier voisin du sommet courant*/
	TypVoisins* temp = graphe->listesAdjacences[sommetCourant];
	
	/*creation du voisin*/
	suivant = creationVoisin(sommetVoisin, poidsVoisinSuivant, temp);
	if(suivant == NULL)
		return -1;
	
	/*Insertion du voisin dans la liste du sommetCourant*/
	graphe->listesAdjacences[sommetCourant] = suivant;
	printf("Arrete entre les sommets %d et %d de poids %d cree\n", sommetCourant, sommetVoisin, poidsVoisinSuivant);
	return 1;
}

/*
* Fonction : suppressionArrete
*
* Parametres : 	int sommetCourant
*				int poidsVoisinSuivant
*				int sommetVoisin
*				Pointeursur tableau de TypVoisins
*
* Retour : entier
*
* Description : Supprime une arrete entre le sommetCourant et le voisin de poids poidsVoisinSuivant
*
*/
int suppressionArrete(int sommetCourant, int sommetVoisin, int poidsVoisinSuivant, TypGraphe* graphe){
	TypVoisins* suivant = NULL;
	TypVoisins* temp = NULL;
	TypVoisins* temp2 = NULL;
	
	/*Si le graphe en entree n'existe pas*/
	if(graphe == NULL || graphe->listesAdjacences == NULL){
		printf("Graphe inexistant\n");
		return -1;
	}
	/*Si le sommet en entree n'est pas dans le graphe ou si il n'est pas encore cree*/
	if(sommetCourant >= graphe->nbMaxSommet || graphe->listesAdjacences[sommetCourant] == NULL){
		//printf("Le sommet de depart choisi est incorrect\n");
		return -2;
	}
	/*Si le voisin en entree n'est pas dans le graphe ou si il n'est pas encore cree*/
	if(sommetVoisin >= graphe->nbMaxSommet || graphe->listesAdjacences[sommetVoisin] == NULL){
		//printf("Le voisin choisi est incorrect\n");
		return -3;
	}
	/*Si l'arrete n'existe pas*/
	if(!arreteExistante(sommetCourant, sommetVoisin, poidsVoisinSuivant, graphe->listesAdjacences)){
		//printf("Arrete entre les sommets %d et %d de poids %d inexistante\n", sommetCourant, sommetVoisin, poidsVoisinSuivant);
		return -4;
	}
	
	/*Sauvegarde du pointeur du premier voisin du sommet courant*/
	temp = graphe->listesAdjacences[sommetCourant];
	
	/*Si le premier voisin est celui a supprime*/
	if(temp->voisin == sommetVoisin && temp->poidsVoisin == poidsVoisinSuivant){
		graphe->listesAdjacences[sommetCourant] = temp->voisinSuivant;
		free(temp);
	}else{ /*Sinon*/
		/*tant que l'on a pas atteint le voisin a supprime*/
		while(temp->voisin != sommetVoisin && temp->poidsVoisin != poidsVoisinSuivant){
			temp2 = temp;
			temp = temp->voisinSuivant;
		}
		temp2->voisinSuivant = temp->voisinSuivant;
		free(temp);
	}
	
	printf("Arrete entre les sommets %d et %d de poids %d supprimee\n", sommetCourant, sommetVoisin, poidsVoisinSuivant);
	return 1;
		
}

/*
* Fonction : destructionGraphe
*
* Parametres : 	TypGraphe** g
*
* Retour : entier
*
* Description : Detruit un graphe
*
*/
int destructionGraphe(TypGraphe** g){
	printf("Destruction du graphe courant\n");
	if(*g == NULL || (*g)->listesAdjacences == NULL){
		printf("Graphe inexistant\n");
		return -1;
	}
	
	int i;
	TypVoisins* temp;
	/*Parcours de chaque sommet potentiel du graphe*/
	for(i = 0; i < (*g)->nbMaxSommet; i++){	
		suppressionArreteSommet(i, *g);
	}
	free((*g)->listesAdjacences);	
	free(*g);
	return 1;
}

/*
* Fonction : affichageGraphe
*
* Parametres : 	TypGraphe* g
*
* Retour : void
*
* Description : Affiche le graphe passe en parametre
*
*/

int affichageGraphe(TypGraphe* g){
	int i;
	TypVoisins* temp;
	system("clear");
	
	if(g==NULL){
		printf("Graphe inexistant\n");
		return -1;
	}
	
	printf("# Nombre maximum de sommets\n");
	printf("%d\n", g->nbMaxSommet);
	printf("# sommets : voisins\n");
	
	/*Parcours de chaque sommet potentiel du graphe*/
	for(i = 0; i < g->nbMaxSommet; i++){	
		temp = g->listesAdjacences[i];
		if(temp != NULL){
			printf("%d : ", i);
			/*Parcrous de tous les voisins d'un sommet donne*/
			while(temp != NULL){
				/*Si on est pas sur le voisin fictif*/
				if(temp->voisin != -1){
					printf("(%d/%d)", temp->voisin, temp->poidsVoisin);
					if(temp->voisinSuivant->voisin != -1)
						printf(", ");
				}
				temp = temp->voisinSuivant;
			}
			printf("\n");
		}
	}	
}

/*
* Fonction : sauvegardeGraphe
*
* Parametres : 	char* nomFichier
* 				TypGraphe* g
*
* Retour : void
*
* Description : Sauvegarde le graphe passe en parametre. Ecrase les donnees automatiquement. Verification de l'existence du
* 				fichier faite dans l'actionManager
*
*/
int sauvegardeGraphe(char* repertoire, char* nomFichier, TypGraphe* g){
	int i;
	TypVoisins* temp;
	char pathFile[255] = "";
	strcat(pathFile, repertoire);
	strcat(pathFile, nomFichier);
	if(g==NULL){
		printf("Graphe inexistant\n");
		return -1;
	}
	FILE* fichier = NULL;
	fichier = fopen(pathFile, "w+");
	if(fichier == NULL){
		printf("Erreur a l'ouverture du fichier %s", pathFile);
		return -1;
	}
	
	fprintf(fichier, "# Nombre maximum de sommets\n");
	fprintf(fichier, "%d\n", g->nbMaxSommet);
	fprintf(fichier, "# sommets : voisins\n");
	
	/*Parcours de chaque sommet potentiel du graphe*/
	for(i = 0; i < g->nbMaxSommet; i++){	
		temp = g->listesAdjacences[i];
		if(temp != NULL){
			fprintf(fichier, "%d : ", i);
			/*Parcrous de tous les voisins d'un sommet donne*/
			while(temp != NULL){
				/*Si on est pas sur le voisin fictif*/
				if(temp->voisin != -1){
					fprintf(fichier, "(%d/%d)", temp->voisin, temp->poidsVoisin);
					if(temp->voisinSuivant->voisin != -1)
						fprintf(fichier, ", ");
				}
				temp = temp->voisinSuivant;
			}
			fprintf(fichier, "\n");
		}
	}	
	fclose(fichier);
	printf("Sauvegarde effectuee : %s\n", pathFile);
	return 1;
}

/*
* Fonction : suppressionArreteSommet
*
* Parametres : 	int sommet
* 				TypGraphe* graphe
*
* Retour : int
*
* Description : supprime toutes les arretes sur un sommet donne
*
*/
int suppressionArreteSommet(int sommet, TypGraphe* graphe){
	TypVoisins* temp;
	TypVoisins* temp2;
	
	temp = graphe->listesAdjacences[sommet];
	while(temp != NULL){
		temp2 = temp->voisinSuivant;
		free(temp);
		temp = temp2;
	}
	graphe->listesAdjacences[sommet] = NULL;
	return 0;
}