#ifndef REGLE_H
#define REGLE_H

#include "listeCommandes.h"
#include <sys/types.h> // Pour time_t
#include <stdio.h>

struct regle{
	char* nom;
	char** prerequis;
	int lenPrerequis;
	listeCommandes* commandes;
	time_t lastModified; // La dernière modification (en secondes)
	int hashModified; // Booléen signifiant s'il y a eu une modification depuis la dernière fois (pour le hash)
};

typedef struct regle regle; // Creation de la regle

regle* createRegle(char* nom, char** prerequis, int lenPrerequis, listeCommandes* commandes);
void freeRegle(regle* r, int isPseudo); // Le booléen nous permet de savoir s'il s'agit d'une pseudo-règle ou pas

regle* createRegleHash(char* nom, char** prerequis, int lenPrerequis, listeCommandes* commandes);

void updateLastModified(regle* r);
time_t getLastModified(char* file); // Récupère la date de modification du fichier
int estFichier(char* nom); // Vérifie si la règle réfère à un fichier

int hashWasModified(char* nom); // Vérifie s'il y a eu une modification du hash depuis la dernière fois
void updateHash(char* nom, unsigned long hash, FILE* f); // Modifie le nouveau hash


#endif