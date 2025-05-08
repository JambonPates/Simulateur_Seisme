#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define capacitePompier 4
#define capaciteAmbulance 2
#define capaciteRavi 10


//--------------------- Structures ------------------------

typedef struct {
    int type;
    int capacite;
    vehicule* suivant;
} vehicule;

typedef struct vehicules* vehicules;

//enum typeVehicule : {"Pompier", "Ambulance", "Ravitaillement"};


//--------------------- Fonctions ------------------------

vehicule* creerListeVehicule(int quantite);
void afficherListeVehicule(vehicule* liste);
void freeVehicules(vehicule* liste);