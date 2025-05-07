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

typedef struct {
    int type;
    int capacite;
} vehicule;



matrice* CreateGraph(int* size);
void afficherRoutes(matrice* Map);
void afficherCheminsAccessibles(matrice* Map, int depart);
void afficherSommetsInaccessibles(matrice* Map, int depart);
void faireSeisme(matrice* Map);
void freeGraph(matrice* Map);