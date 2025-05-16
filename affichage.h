#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdbool.h>

typedef struct {
    int distance;
    int etat;
    int capacite;
    bool existe;
    bool surbrillance;
} route;

typedef struct {
    int nbSommets;
    route** adjacence;
} matrice;

matrice* creerGraphe(int* taille);
void libererGraphe(matrice* carte);
void afficherRoutes(matrice* carte);
void afficherSommetsInaccessibles(matrice* carte);
void faireSeisme(matrice* carte);
void reinitialiserSurbrillance(matrice* carte);
void parcoursEnProfondeur(matrice* carte, bool afficherInaccessibles);
void parcoursEnLargeur(matrice* carte, bool afficherArcs);
void composantesFortementConnexes(matrice* carte);
void identifierRoutesImportantes(matrice* carte);

#endif
