#include "vehicules.h"


tete* creerListeVehicule(int quantite){
    //Créer la liste chgainée et remplie si besoin

    // création de la tête 
    tete* pListe = malloc(sizeof(tete));

    if (pListe == NULL){

        printf("Erreur allocation tête\n");
        exit(-1);

    }

    pListe->adresse = NULL;

    if (quantite <= 0){
        return pListe;
    }
        

    for (int i = 0; i  < 10; i++){
        
    }

    // ajout des véhucles
    vehicule* premier = malloc(sizeof(vehicule));

    if (premier == NULL){ 

        printf("Erreur allocation premier véhicule\n");
        exit(-1);

    }

    premier->type = 1;
    premier->capacite = capacitePompier;
    premier->suivant = NULL;
    pListe->adresse = premier;

    vehicule* courant = premier;

    for (int i = 1; i < quantite; i++){

        vehicule* new = malloc(sizeof(vehicule));

        if (new == NULL){
            printf("Erreur allocation véhicule\n");
            exit(-1);
        }

        new->type = 1;
        new->capacite = capacitePompier;
        new->suivant = NULL;

        courant->suivant = new;
        courant = new;

    }

    return pListe;
}


void afficherListeVehicule(tete* liste){
    // Affiche tous les véhicules de la liste

    printf("Liste des Véhicules :\n\n");

    vehicule* courant = liste->adresse;

    while (courant != NULL){

        printf("Type : %d, capacite : %d\n", courant->type, courant->capacite);
        courant = courant->suivant;

    }

}


void freeVehicules(tete* liste){
    // Libère toutes les allocations du aux véhicules

    vehicule* courant = liste->adresse;

    while (courant != NULL){

        vehicule* tmp = courant;
        courant = courant->suivant;
        free(tmp);

    }

    free(liste); 
}

// int main() {
//     tete* maListe = creerListeVehicule(5);
//     afficherListeVehicule(maListe);
//     freeVehicules(maListe);
//     return 0;
// }
