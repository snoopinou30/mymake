#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lectureMakefile.h"
#include "listeRegles.h"
#include "regle.c"
#include "listeRegles.c"


// Cree une liste vide de commandes (= le pointeur NULL)
listeCommandes_t* createListeCommands(void){
	return NULL;
}

// Libere une liste de commandes (sans libérer les commandes elles-mêmes)
void freeListeCommands(listeCommandes_t* c){
	if(c != NULL){
		listeCommandes_t* next = c->next;
		free(c);
		freeListeCommands(next);
	}
}

// Ajoute une commande [r] a la liste de commandes [list]
listeCommandes_t* addCommande(listeCommandes_t* list, char* c){
	listeCommandes_t* retList = malloc(sizeof(listeCommandes_t));
	retList->commande = c;
	retList->next = list;
	return retList;
}



listeRegles_t* makefile2list(FILE *makefile){
	char *ligne_buffer = NULL;
	size_t tailleLigne_buffer;
	ssize_t tailleLigne;
	
	bool push = true; // Booléen disant si la dernière règle a été incluse dans la liste de règles
	char *token;
	regle_t* nouvelleRegle = createRegle(token, NULL , 0, NULL, 0);
	listeRegles_t* liste;
	tailleLigne = getline(&ligne_buffer, &tailleLigne_buffer, makefile); // Première ligne du fichier

	while(tailleLigne>=0){
		if (tailleLigne == 1){	// Ligne vide
			if (!push){ // On ajoute la règle si ce n'est déjà fait (il peut y avoir plusieurs \n)
				addRegle(liste, nouvelleRegle);
				push = true;
			}
			else {}
		}
		else if (*ligne_buffer != 9) { // pas de tabulation -> nouvelle règle !
			push = false;
			token = strtok(ligne_buffer, ":"); // D'abord le nom de la règle (avant ":")
			printf("Nom nouvelleRegle : %s\n", token);
			int lenPrerequis = 0;
			
			token = strtok(NULL, " "); // Comptage du nombre de prérequis
			
			while(token != NULL) {
				lenPrerequis++;
				token = strtok(NULL, " ");
			};

			char* prerequis[lenPrerequis];
			token = strtok(ligne_buffer, ":"); // On repart à 0
			token = strtok(NULL, " ");
			for (int i=0 ; i< lenPrerequis; i++) {
				prerequis[i] = token;
				token = strtok(NULL, " "); // Suivant !
			};
			nouvelleRegle->lenPrerequis = lenPrerequis;
			nouvelleRegle->prerequis = prerequis;
			
			printf("Nombre prerequis : %d\n", lenPrerequis);
		}
		else { // C'est une commande !
			ligne_buffer++; // Pour négliger la tabulation, on saute une case mémoire (optionnel)
			printf("Commande : %s\n", ligne_buffer);
			(nouvelleRegle->lenCommandes)++;
		}

		tailleLigne = getline(&ligne_buffer, &tailleLigne_buffer, makefile); // Nouvelle ligne
	}
}

listeRegles_t* main(){
	makefile2list(fopen("Makefile", "r"));
}