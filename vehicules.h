#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define capacitePompier 4
#define capaciteAmbulance 2
#define capaciteRavi 10


//--------------------- Structures ------------------------

typedef struct vehicule {
    int type;
    int capacite;
    struct vehicule* suivant;
} vehicule;

typedef struct {
    vehicule* adresse;
} tete;



enum typeVehicule {Pompier = 1, Ambulance = 2, Ravitaillement = 3};


//--------------------- Fonctions ------------------------

tete* creerListeVehicule(int quantite);
void afficherListeVehicule(tete* liste);
void freeVehicules(tete* liste);