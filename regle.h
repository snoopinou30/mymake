#ifndef REGLE_H
#define REGLE_H

#include "lectureMakefile.h"

struct regle{
	char* nom;
	char** prerequis;
	int lenPrerequis;
	listeCommandes_t* commandes;
	time_t lastModified; // La dernière modification (en secondes)
};

typedef struct regle regle_t; // Creation de la regle

regle_t* createRegle(char* nom, char** prerequis, int lenPrerequis, listeCommandes_t* commandes);
void freeRegle(regle_t* r);

time_t getLastModified(char* file); // Récupère la date de modification du fichier
int estFichier(regle_t* regle); // Vérifie si la règle réfère à un fichier

#endif