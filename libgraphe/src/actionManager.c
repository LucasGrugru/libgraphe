/*
 * TypGraphe.c
 *
 *  Created on: 29 janv. 2013
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include "actionManager.h"
#include "TypGraphe.h"


/*
* Fonction : FileExists
*
* Parametres : 	char* FileName
*
* Retour : int
*
* Description : Test l'existence d'un fichier. Ne fonctionne que si on a les permissions sur le fichier teste
*
*/
int FileExists(char* FileName, char* folderName)
{
    FILE* fp = NULL;
	char pathFile[255] = "";
	strcat(pathFile, folderName);
	strcat(pathFile, FileName);

    fp = fopen( pathFile, "rb" );
    if( fp != NULL )
    {
        fclose( fp );
        return 1;
    }

    return 0;
}

/*
* Fonction : cutFolderFileNameWithCreate
*
* Parametres : 	char* c
* 				char** nameFolder
* 				char** nameFile
* 				
*
* Retour : char*
*
* Description : Retourne le nom du dossier issu de la chaine passe en parametre et creer les dossier du chemin a la volee
*
*/
void cutFolderFileNameWithCreate(char* c, char** nameFolder, char** nameFile){
	char cc[251];
	char* slash = "/" ; 
	int nbSlash = 0, i;
	strcpy(*nameFolder, "");
	strcpy(*nameFile, "");
	strcpy(cc, c);
	
	/*Compte le nombre de Slash*/
	char* p = strtok (cc, slash); 
	while (p != NULL) 
	{ 
		nbSlash++;
		p = strtok (NULL, slash); 
	}
	strcpy(cc, c);
	/*on parcours maintenant a nouveau la chaine en ne copiant que le chemin du dossier*/
	for(i = 0; i<nbSlash-1; i++){
		if(i == 0)
			p = strtok (cc, slash);
		else
			p = strtok (NULL, slash);
		*nameFolder = strcat(*nameFolder, p);
		*nameFolder = strcat(*nameFolder, "/");		
		/*On cree le dossier de destination*/
		mkdir(*nameFolder, 01777);
	}
	/*Differencie si la chaine a decouper contient uniquement le nom de fichier*/
	if(nbSlash <= 1)
		p = strtok (cc, slash);
	else
		p = strtok (NULL, slash);
	*nameFile = strcat(*nameFile, p);
}

/*
* Fonction : actionManager
*
* Parametres : 	int c
* 				TypeGraphe* g
*
* Retour : int
*
* Description : Manager des actions realisees en fonction du choix de l'utilisateur.
*
*/
int actionManager(int c, TypGraphe** g, int* possibilite) {
	char* s;
	/*Quitter l'application*/
	if(c == 1) {
		destructionGraphe(g);
		printf("Fermeture de l'application\n");
		exit(0);
	}
	/*Creer un graphe*/
	else if(c == 2) {
		int nbSommet;
		char supp = 'a';
		
		/*Si un graphe existe, on demande a l utilisateur si il veut l ecraser*/
		if(*g != NULL){
			s = "Voulez vous supprimer le graphe courant?[o : Supprimer / n : Annuler]\n";
			supp = acquisitionReponseON(s);
			if(supp == 'o')
				destructionGraphe(g);
			else
				return 0;
		}
		
		s = "Combien de sommet maximum pour le graphe?\n";
		nbSommet = acquisitionInteger(s);
		
		*g = creationGraphe(nbSommet);
		if(g == NULL){
			printf("Erreur a la creation du graphe : Erreur d'allocation\n");
		}
		*possibilite = 1;
		return 1;	
	} 
	/*Import d'un graphe*/
	else if(c == 3) {
		*possibilite = 1;
	}
	/*Affichage d'un graphe*/
	else if(c == 4 && *possibilite == 1) {
		affichageGraphe(*g);
	}
	/*Ajout d'un sommet*/
	else if(c == 5 && *possibilite == 1) {
		int numeroSommet;
		s = "Quel sommet creer?\n";
		numeroSommet = acquisitionInteger(s);
		ajoutSommet(numeroSommet, *g);
	}
	/*Suppression d'un sommet*/
	else if(c == 6 && *possibilite == 1) {
		int numeroSommet;
		s = "Quel sommet supprimer?\n";
		numeroSommet = acquisitionInteger(s);
		suppressionSommet(numeroSommet, *g);
	}
	/*Ajout d'une arrete*/
	else if(c == 7 && *possibilite == 1) {
		int numeroSommet, numeroVoisin, poids;
		char oriente = 'a';
		
		s = "Quel sommet de depart?\n";
		numeroSommet = acquisitionInteger(s);
		s = "Quel sommet voisin?\n";
		numeroVoisin = acquisitionInteger(s);
		s = "Quel poids?\n";
		poids = acquisitionInteger(s);
		s = "Arrete oriente? [o/n]?\n";
		oriente = acquisitionReponseON(s);
		insertionArrete(numeroSommet, numeroVoisin, poids, *g);
		if(oriente == 'n'){
			insertionArrete(numeroVoisin, numeroSommet, poids, *g);	
		}
	}
	/*Suppression d'une arrete*/
	else if(c == 8 && *possibilite == 1) {
		int numeroSommet, numeroVoisin, poids;
		char oriente = 'a';
		
		s = "Quel sommet de depart?\n";
		numeroSommet = acquisitionInteger(s);
		s = "Quel sommet voisin?\n";
		numeroVoisin = acquisitionInteger(s);
		s = "Quel poids?\n";
		poids = acquisitionInteger(s);
		s = "Arrete oriente? [o/n]?\n";
		oriente = acquisitionReponseON(s);
		suppressionArrete(numeroSommet, numeroVoisin, poids, *g);
		if(oriente == 'n'){
			suppressionArrete(numeroVoisin, numeroSommet, poids, *g);	
		}
	}
	/*Sauvegarde d'un graphe*/
	else if(c == 9 && *possibilite == 1) {
		/*chemin de fichier limite a 251 caracteres. Limitation des systemes FAT32 a 255 + extension .txt*/
		char pathFile[251];
		char ecraser = 'a';
		char* nameFile = (char*)malloc(251 * sizeof(char));;
		char* nameFolder = (char*)malloc(251 * sizeof(char));
		printf("Entrez le chemin du fichier desire : \n");
		fgets(pathFile, sizeof(pathFile), stdin);
		/* Nettoyage de la chaine*/
		char *p = strchr(pathFile, '\n');
		if (p)
		{
			*p = 0;
		}
		/*On recupere le chemin et le nom de fichier separement*/
		cutFolderFileNameWithCreate(pathFile, &nameFolder, &nameFile);
		/*On ajoute l'extension*/
		strcat(nameFile, ".txt");
		/*Si le fichier existe, on dmeande si l'utilisateur souhaite l'ecraser*/
		if(FileExists(nameFile, nameFolder))
		{
			s = "Fichier existant, ecraser? [o/n]?\n";
			ecraser = acquisitionReponseON(s);
			if(ecraser == 'o')
				sauvegardeGraphe(nameFolder, nameFile, *g);
		}
		else
			sauvegardeGraphe(nameFolder, nameFile, *g);
		free(nameFile);
		free(nameFolder);
	}

	return 0;
}

/*Les deux fonctions suivantes permettent de nettoyer le buffer correctement apres un saisie de caractere au clavier*/
void purger(void)
{
    int c;
 
    while ((c = getchar()) != '\n' && c != EOF)
    {}
}
 
void clean (char *chaine)
{
    char *p = strchr(chaine, '\n');
 
    if (p)
    {
        *p = 0;
    }
 
    else
    {
        purger();
    }
    
    p = strchr(chaine, '-');
    if (p)
    {
		*p = 0;
	}
}

/*
* Fonction : acquisitionInteger
*
* Parametres : char* s
*
* Retour : int
*
* Description : Ecrit le texte en parametre et retourne l'entier entre par l'utilisateur
*
*/
int acquisitionInteger(char* s){
	int i, ret;
	/*On limite la taille d'un entier a 10 caractere (integer code sur 8bits)*/
	char c[10];
	
	 do{
		/* Entre du nombre */
		printf("%s", s);
		fgets(c, sizeof(c), stdin);
 
		/* Nettoyage de la chaine et du stdin */
		clean(c);
 
		/* Conversion chaine */
		ret = sscanf(c, "%d", &i);
	} while (ret != 1);
	
	return i;
}

/*
* Fonction : acquisitionReponseON
*
* Parametres : char* s
*
* Retour : char
*
* Description : Ecrit le texte en parametre et retourne la reponse entre par l'utilisateur
*
*/
char acquisitionReponseON(char* s){
	int i;
	char ret;
	/*On limite la taille d'un entier a 10 caractere (integer code sur 8bits)*/
	char c = 'a';
	
	while(c != 'o' && c != 'n'){
		printf("%s", s);
		scanf("%1[o,n]", &c);
		/*Vide le buffer : Permet d'eviter des problemes en cas de saisie de mauvais caractere*/
		scanf ("%*[^\n]");
		getchar ();
	}
	return c;
}

