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
* Fonction : reInitialisationChar
*
* Parametres : 	Typgraphe* graphe
* 				FILE* file
* 				int sommet
*
* Retour : int
*
* Description : Reinitialise la chaine en parametre faisant une certaine taille avec des caracteres vides
*
*/
void reInitialisationChar(char c[], int taille){
	int i;
	for(i=0 ; i<taille ; i++){
		c[i] = ' ';
	}
}
/* Les deux fonctions suivantes permettent de nettoyer le buffer correctement 
 * apres un saisie de caractere au clavier ou dans un fichier
 */
void purgerS(void)
{
    int c;
 
    while ((c = getchar()) != '\n' && c != EOF)
    {}
}
 
void cleanS (char *chaine)
{
    char *p = strchr(chaine, '\n');
 
    if (p)
    {
        *p = 0;
    }
 
    else
    {
        purgerS();
    }
    
    p = strchr(chaine, '-');
    if (p)
    {
		*p = 0;
	}
}

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
int creationGraphe(int nbMaxSommet,TypGraphe** graphe) {
	int i;
	if(*graphe == NULL)
		*graphe = (TypGraphe*)malloc(sizeof(TypGraphe));
	if(*graphe == NULL)
		return ERROR_CREATE_GRAPHE;

	TypVoisins** listeAdjacences;
	listeAdjacences = (TypVoisins**) malloc(nbMaxSommet * sizeof(TypVoisins*));
	/*Initialisation de la liste d'adjacence*/
	for(i=0; i<nbMaxSommet; i++) {
		listeAdjacences[i] = NULL;
	}
	/*Initialisation des variable de la structure du graphe*/
	(*graphe)->nbMaxSommet = nbMaxSommet;
	(*graphe)->listesAdjacences = listeAdjacences;
	return SUCCESS_CREATE_GRAPHE;
}

/*
* Fonction : nextLine
*
* Parametres : 	FILE* file
*
* Retour : 
*
* Description : Saute une ligne dans le fichier en parametre
*
*/
int nextLine(FILE* file){
	unsigned int i, retour;
	char* tChaine = NULL;
	retour = getline(&tChaine, &i, file);
	free(tChaine);
	return retour;
}

/*
* Fonction : getSommetInFile
*
* Parametres : 	Typgraphe* graphe
* 				FILE* file
* 				int ajout
*
* Retour : int
*
* Description : retourne un sommet issue du fichier et l'ajoute au graphe si ajout est vrai.
*
*/
int getSommetInFile(TypGraphe* graphe, FILE* file, int ajout){
	char c;
	char chaine[10] = "";
	int i = 0;
	/*Lit tous les caracteres jusqu'a rencontre un espace*/
	while(i < 10 && (c = fgetc(file)) != ' ' && c != EOF){
		chaine[i] = c;		
		i++;
	}
	if(c != EOF && ajout)
		ajoutSommet(atoi(chaine), graphe);
	return atoi(chaine);
}

/*
* Fonction : allSommetInFile
*
* Parametres : 	FILE* file
* 				TypGraphe* graphe
*
* Retour : 
*
* Description : Ajoute tous les sommets du fichier dans le graphe et retourne le nombre de sommets crees
*
*/
int allSommetInFile(FILE* file, TypGraphe* graphe){
	int nbSommet = 0;
	while(nextLine(file) != -1){
		nbSommet++;
		getSommetInFile(graphe, file, 1);
	}
	return nbSommet;
}

/*
* Fonction : recupererTailleMaxGrapheInFile
*
* Parametres : 	FILE* file
*
* Retour : int
*
* Description : retourne la taille du graphe inscrite dans le fichier passe en parametre
*
*/
int recupererTailleMaxGrapheInFile(FILE* file){
	char chaine[30];
	nextLine(file);
	fgets(chaine, 10, file);
	cleanS(chaine);
	return atoi(chaine);
}

/*
* Fonction : getArreteInFile
*
* Parametres : 	Typgraphe* graphe
* 				FILE* file
* 				int sommet
*
* Retour : int
*
* Description : ajoute les arretes d'un sommet issues d'un fichier dans le graphe 
*
*/
void getArreteInFile(TypGraphe* graphe, FILE* file, int sommet){
	char c = 'a';
	char voisin[10] = "";
	char poids[10] = "";
	int i = 0;
	while(c != '\n' && c != EOF){
		reInitialisationChar(poids, sizeof(poids));
		reInitialisationChar(voisin, sizeof(voisin));
		i = 0;
		/*Lit tous les caracteres jusqu'a rencontre une accolade ouvrante (debut de l'indication d'une arrete)*/
		while((c = fgetc(file)) != '(' && c != EOF && c != '\n');
		/*On stocke dans la voisin tout ce qui est compris entre l'accolade ouvrant et le slash */
		while(c != '\n' && (c = fgetc(file)) != '/' && c != EOF ){
			voisin[i] = c;	
			i++;
		}
		i = 0;
		/*On stocke dans la poids tout ce qui est compris entre le slash et l'accolade fermante*/
		while(c != '\n' && (c = fgetc(file)) != ')' && c != EOF){
			poids[i] = c;	
			i++;
		}
		if(c != EOF)
			insertionArrete(sommet, atoi(voisin), atoi(poids), graphe);
	}
}

/*
* Fonction : allArreteInFile
*
* Parametres : 	FILE* file
* 				TypGraphe* graphe
*
* Retour : 
*
* Description : Ajoute toutes les arretes du fichier dans un graphe contenant nbSommet sommets
*
*/
void allArreteInFile(FILE* file, TypGraphe* graphe, int nbSommet){
	int i;
	/*On parcours les lignes du fichier avec les informations sur les sommets et leurs arretes*/
	for(i=0; i<nbSommet-1; i++){
		getArreteInFile(graphe, file, getSommetInFile(graphe, file, 0));
		nextLine(file);
	}
}

/*
* Fonction : importGraphe
*
* Parametres : 	char* pathFile
*				TypGraphe* 
*
* Retour : int
*
* Description : importe un graphe depuis le fichier en parametre
*
*/
int importGraphe(char* pathFile, TypGraphe** graphe){
	int tailleMaxGraphe, nbSommet;
	/*Ouverture du fichier en lecture seule*/
	FILE* fichier = NULL;
	fichier = fopen(pathFile, "rb");
	if(fichier == NULL)
		return ERROR_OPEN_FILE;
	
	/*On recupere la taille max du graphe*/
	tailleMaxGraphe = recupererTailleMaxGrapheInFile(fichier);
	/*On cree le graphe*/
	creationGraphe(tailleMaxGraphe,graphe);
	//TODO Verifier la bonne creation du graphe
	/*On parcours toutes les lignes restante pour obtenir les sommets existants*/
	/*On doit lire tous les sommets avant d'ajouter les arretes car une arretes doit*/
	/*avoir un sommet de depart et d'arrive existant dans le graphe*/
	nbSommet = allSommetInFile(fichier, *graphe);
	/*Replacement au debut du fichier*/
	rewind(fichier);
	nextLine(fichier);
	nextLine(fichier);
	nextLine(fichier);
	allArreteInFile(fichier, *graphe, nbSommet);
	fclose(fichier);
	return SUCCESS_IMPORT_GRAPHE;
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
	if(graphe == NULL || graphe->listesAdjacences == NULL)
		return ERROR_NOT_GRAPHE;
	if(sommet > graphe->nbMaxSommet)
		return ERROR_SOMMET_OUT_OF_RANGE;
	if(graphe->listesAdjacences[sommet] != NULL)
		return ERROR_EXISTING_SOMMET;
	
	TypVoisins* voisinFactice = creationVoisinFactice();
	if(voisinFactice == NULL)
		return ERROR_CREATE_SOMMET;
	
	graphe->listesAdjacences[sommet] = voisinFactice;
	return SUCCESS_ADD_SOMMET;
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
	TypVoisins* temp = NULL;
	TypVoisins* temp2 = NULL;
	/*Si le graphe en entree n'existe pas*/
	if(graphe == NULL || graphe->listesAdjacences == NULL)
		return ERROR_NOT_GRAPHE;
	/*Si le sommet en entree n'est pas dans le graphe ou si il n'est pas encore cree*/
	if(sommetCourant >= graphe->nbMaxSommet || graphe->listesAdjacences[sommetCourant] == NULL)
		return ERROR_BAD_SOMMET;
	/*Si le voisin en entree n'est pas dans le graphe ou si il n'est pas encore cree*/
	if(sommetVoisin >= graphe->nbMaxSommet || graphe->listesAdjacences[sommetVoisin] == NULL)
		return ERROR_BAD_VOISIN;
	/*Si l'arrete n'existe pas*/
	if(!arreteExistante(sommetCourant, sommetVoisin, poidsVoisinSuivant, graphe->listesAdjacences))
		return ERROR_NOT_EXISTING_ARRETE;
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
	return SUCCESS_DELETE_ARRETE;	
}

/*
* Fonction : suppressionArreteSommet
*
* Parametres : 	int sommet
* 				TypGraphe* graphe
*
* Retour :
*
* Description : supprime toutes les arretes sur un sommet donne
*
*/
void suppressionArreteSommet(int sommet, TypGraphe* graphe){
	TypVoisins* temp;
	TypVoisins* temp2;
	
	temp = graphe->listesAdjacences[sommet];
	while(temp != NULL){
		temp2 = temp->voisinSuivant;
		free(temp);
		temp = temp2;
	}
	graphe->listesAdjacences[sommet] = NULL;
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
	if(graphe == NULL || graphe->listesAdjacences == NULL)
		return ERROR_NOT_GRAPHE;
	if(sommet > graphe->nbMaxSommet)
		return ERROR_SOMMET_OUT_OF_RANGE;
	if(graphe->listesAdjacences[sommet] == NULL)
		return ERROR_NOT_EXISTING_SOMMET;
	/*On supprime tous les voisins du sommet choisi*/
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
	return SUCCESS_DELETE_SOMMET;
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
	if(graphe == NULL || graphe->listesAdjacences == NULL)
		return ERROR_NOT_GRAPHE;
	/*Si le sommet en entree n'est pas dans le graphe ou si il n'est pas encore cree*/
	if(sommetCourant >= graphe->nbMaxSommet || graphe->listesAdjacences[sommetCourant] == NULL)
		return ERROR_BAD_SOMMET;
	/*Si le voisin en entree n'est pas dans le graphe ou si il n'est pas encore cree*/
	if(sommetVoisin >= graphe->nbMaxSommet || graphe->listesAdjacences[sommetVoisin] == NULL)
		return ERROR_BAD_VOISIN;
	/*Si l'arrete existe deja*/
	if(arreteExistante(sommetCourant, sommetVoisin, poidsVoisinSuivant, graphe->listesAdjacences))
		return ERROR_EXISTING_ARRETE;
	
	/*Sauvegarde du pointeur du premier voisin du sommet courant*/
	TypVoisins* temp = graphe->listesAdjacences[sommetCourant];
	/*creation du voisin*/
	suivant = creationVoisin(sommetVoisin, poidsVoisinSuivant, temp);
	if(suivant == NULL)
		return ERROR_DELETE_ARRETE;
	/*Insertion du voisin dans la liste du sommetCourant*/
	graphe->listesAdjacences[sommetCourant] = suivant;
	return SUCCESS_INSERTION_ARRETE;
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
	if(*g == NULL || (*g)->listesAdjacences == NULL)
		return ERROR_NOT_GRAPHE;
	
	int i;
	/*Parcours de chaque sommet potentiel du graphe*/
	for(i = 0; i < (*g)->nbMaxSommet; i++){	
		suppressionArreteSommet(i, *g);
	}
	free((*g)->listesAdjacences);	
	free(*g);
	*g = NULL;
	return SUCCESS_DELETE_GRAPHE;
}

/*
* Fonction : affichageGraphe
*
* Parametres : 	TypGraphe* g
*
* Retour : void
*
* Description : Affiche le graphe passe en parametre. 
*
*/
int affichageGraphe(TypGraphe* g){
	int i;
	TypVoisins* temp;
	system("clear");
	if(g==NULL)
		return ERROR_NOT_GRAPHE;

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
	return SUCCESS_PRINT_SCREEN;
}

/*
* Fonction : sauvgardeSommetArrete
*
* Parametres : 	char* nomFichier
* 				TypGraphe* g
*
* Retour : void
*
* Description : Sauvegarde dans le fichier des lignes concernant les sommets et leurs arretes
*
*/
void sauvgardeSommetArrete(FILE* fichier, TypGraphe* g){
	int i;
	TypVoisins* temp;
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
	char pathFile[255] = "";
	strcat(pathFile, repertoire);
	strcat(pathFile, nomFichier);
	if(g==NULL){
		return ERROR_NOT_GRAPHE;
	}

	/*Ouverture du fichier en mode w+*/
	FILE* fichier = NULL;
	fichier = fopen(pathFile, "w+");
	if(fichier == NULL){
		return ERROR_OPEN_FILE;
	}
	fprintf(fichier, "# Nombre maximum de sommets\n");
	fprintf(fichier, "%d\n", g->nbMaxSommet);
	fprintf(fichier, "# sommets : voisins\n");
	sauvgardeSommetArrete(fichier, g);
	fclose(fichier);
	return SUCCESS_SAVE;
}

void messageManager(int err){
	switch(err) 
	{
		case SUCCESS_CREATE_GRAPHE :
			printf("Graphe crée avec succès\n\n");
			break;
		case SUCCESS_IMPORT_GRAPHE :
			printf("Graphe importé avec succès\n\n");
			break;
		case SUCCESS_DELETE_ARRETE :
			printf("Arrete supprimée avec succès\n\n");
			break;
		case SUCCESS_DELETE_SOMMET :
			printf("Sommet supprimé avec succès\n\n");
			break;
		case SUCCESS_INSERTION_ARRETE:
			printf("Arrete ajoutée avec succès\n\n");
			break;
		case SUCCESS_ADD_SOMMET :
			printf("Sommet ajouté avec succès\n\n");
			break;
		case SUCCESS_SAVE :
			printf("Sauvegarde effectuée avec succès\n\n");
			break;
		case SUCCESS_PRINT_SCREEN :
			printf("Affichage effectué avec succès\n");
			break;
		case SUCCESS_DELETE_GRAPHE :
			printf("Suppression du graphe avec succès\n");
			break;		
		case ERROR_CREATE_GRAPHE :
			printf("Erreur à la création du graphe\n\n");
			break;
		case ERROR_OPEN_FILE :
			printf("Erreur à l'ouverture du fichier\n\n");
			break;
		case ERROR_NOT_GRAPHE:
			printf("Aucun graphe courant existant\n\n");
			break;
		case ERROR_SOMMET_OUT_OF_RANGE :
			printf("Erreur : Sommet hors des limites du graphe\n\n");
			break;
		case ERROR_EXISTING_SOMMET :
			printf("Erreur : Sommet déjà existant\n\n");
			break;
		case ERROR_CREATE_SOMMET :
			printf("Erreur à la création du sommet\n\n");
			break;
		case ERROR_BAD_SOMMET :
			printf("Erreur : Mauvais sommet. Véirfiez qu'il existe ou n'est pas hors limite\n\n");
			break;
		case ERROR_BAD_VOISIN :
			printf("Erreur : Mauvais voisin. Véirfiez qu'il existe ou n'est pas hors limite\n");
			break;	
		case ERROR_NOT_EXISTING_ARRETE :
			printf("Erreur : Arrète inexistante\n\n");
			break;
		case ERROR_EXISTING_ARRETE :
			printf("Erreur : Arrete existante\n\n");
			break;
		case ERROR_DELETE_ARRETE: 
			printf("Erreur à la suppression d'une arrete\n\n");
			break;
		case ERROR_NOT_EXISTING_SOMMET :
			printf("Erreur : Sommet inexistant\n\n");
			break;
		default :
			break;
	}
}
