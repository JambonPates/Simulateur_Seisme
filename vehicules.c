#include "vehicules.h"


//-------------------------------------------------------------------------//

vehicule* creerListeVehicule(int quantite){

    if (quantite == 0){
        return NULL;
    }

    vehicule* tete;
    tete = (vehicule*)malloc(sizeof(vehicule));

    if(tete == NULL){

        printf("Erreur Alloc liste vehicules\n");
        exit(-1);

    }

    tete->capacite = capacitePompier;
    tete->type = 1;
    tete->suivant = NULL;

    if(quantite > 1){

        vehicule* vehiculeCourant = tete;

        for (int i = 1; i < quantite; i++){
            vehicule* newVehicule = (vehicule*)malloc(sizeof(vehicule));

            if(newVehicule != NULL){

                newVehicule->capacite = capacitePompier;
                newVehicule->type = 1;
                newVehicule->suivant = NULL;

                vehiculeCourant->suivant = newVehicule;
                newVehicule = NULL;
            }
            else{
                printf("Erreur Allocation NewVehicule\n");
                exit(-1);
            }

        }
    }
    

    return tete;

}


void afficherListeVehicule(vehicule* liste){

    printf("Liste des Véhicules :\n\n");

    while(liste != NULL){

        printf("Type : %d, capacite : %d\n", liste->type, liste->capacite);
    }
}


void freeVehicules(vehicule* liste){

    if (liste != NULL){
        vehicule* tete = liste;
        liste = liste->suivant;

        while(tete != NULL){
            free(tete);
            tete = liste;
            liste = liste->suivant;

        }
        
    }
}

/*
int main(){

    vehicule* maListe;
    maListe = creerListeVehicule(5);
    afficherListeVehicule(maListe);
    free(maListe);

    return 0;
}*/