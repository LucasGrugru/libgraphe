/*
 * main.c
 *
 *  Created on: 29 janv. 2013
 *      Author: lgruber
 */

int menu();
int actionManager(int c);

int main(int argv, char** argc) {

	int choix = menu();
	actionManager(choix);
}

int menu() {
	char* choix;
	printf("Choix ?\n");
	printf("1 : Quitter l'application.\n");
	printf("2 : Création d'un graphe manuellement.\n");
	printf("3 : Import d'un graphe.\n");
	scanf(choix);
	if(atoi(choix) > 0 && atoi(choix) < 4)
		return atoi(choix);
	return 0;
}

int actionManager(int c) {

	if(c == 1) { //quitte l'application

	} else if(c == 2) {

	} else if(c == 3) {

	}

	return 0;
}
