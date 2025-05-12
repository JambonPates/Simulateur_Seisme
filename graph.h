#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ConnexionParSommet 3
#define EtatRouteOrigine 3


//--------------------- Structures ------------------------

typedef struct{
    int distance;
    int etat;      
    int capacite;  
    bool existe;   
    bool surbrillance;
} route;

typedef struct{
    route** Adajacente;
    int nbSommet;
} matrice;


//--------------------- Fonctions ------------------------

matrice* CreateGraph(int* size);
void afficherRoutes(matrice* Map);
void afficherSommetsInaccessibles(matrice* Map);
void parcoursEnProfondeur(matrice* Map, bool afficherSommetInaccessible);
void parcoursEnLargeur(matrice* Map, bool afficherArcs);
void identificationRoutesImportantes(matrice* Map);
void ComposantesFortementConnexes(matrice* Map);
void faireSeisme(matrice* Map);
void ResetSurbrillance(matrice* Map);
void freeGraph(matrice* Map);