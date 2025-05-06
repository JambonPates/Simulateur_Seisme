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
void freeGraph(matrice* Map);

//-------------------------------------------------------------------------//

matrice* CreateGraph(int* size){

    matrice* Map = malloc(sizeof(matrice));

    if (Map == NULL) {
        printf("Erreur d'allocation Map\n");
        exit(-1);
    }

    Map->nbSommet = *size;
    Map->Adajacente = malloc(*size * sizeof(route*));

    if (Map->Adajacente == NULL){

        printf("Erreur d'allocation pour les lignes.\n");

        free(Map);
        exit(-1);

    }
    
    for (int i = 0; i < *size; i++){

        Map->Adajacente[i] = malloc(*size * sizeof(route));

        if (Map->Adajacente[i] == NULL){

            printf("Erreur d'allocation Colonne\n");

            for (int j = 0; j < i; j++){

                free(Map->Adajacente[j]);

            } 

            free(Map->Adajacente);
            free(Map);

            exit(-1);
        }

        for (int j = 0; j < *size; j++) {
            // Initialiser chaque case à "aucun chemin"
            Map->Adajacente[i][j].existe = false;
        }

    }

    for (int i = 0; i < *size; i++){

        int nbVoisins = rand() % 5; 

        for (int k = 0; k < nbVoisins; k++){

            int j = rand() % (*size);
            
            while (j == i || Map->Adajacente[i][j].existe) {
                j = rand() % (*size); 
            }
            
            Map->Adajacente[i][j].existe = true;
            Map->Adajacente[i][j].distance = rand() % 100 + 1;
            Map->Adajacente[i][j].etat = 3; 
            Map->Adajacente[i][j].capacite = rand() % 5 + 1;

        }
    }

    return Map;
}


void afficherRoutes(matrice* Map){

    printf("\n--- Affichage des routes existantes ---\n");

    for (int i = 0; i < Map->nbSommet; i++){
        for (int j = 0; j < Map->nbSommet; j++){

            route r = Map->Adajacente[i][j];

            if (r.existe){
                printf("Route de %d vers %d : Distance = %d, etat = %d, Capacité = %d\n",i, j, r.distance, r.etat, r.capacite);
            }

        }
    }

}


void afficherCheminsAccessibles(matrice* Map, int depart){

    printf("\n--- Chemins accessibles depuis le sommet %d ---\n", depart);

    
    for (int i = 0; i < Map->nbSommet; i++){

        route r = Map->Adajacente[depart][i];

        if (r.existe && r.etat != 0 && r.capacite > 0){

            printf("  -> %d (Distance: %d, Capacité: %d, etat: %d)\n", i, r.distance, r.capacite, r.etat);
        }
    }

}

void afficherSommetsInaccessibles(matrice* Map, int depart){

    printf("\n--- Sommets inaccessibles depuis le sommet %d ---\n", depart);
/*
    for (int i = 0; i < Map->nbSommet; i++) {
        route r = Map->Adajacente[depart][i];
        if (r.existe && r.etat != 0 && r.capacite > 0) {
        }
    }*/
}


void faireSeisme(matrice* Map){

    for (int i = 0; i < Map->nbSommet; i++){
        for (int j = 0; j < Map->nbSommet; j++){
            if (Map->Adajacente[i][j].existe){
                Map->Adajacente[i][j].etat -= rand() % 3 + 1;
                /*if (Map->Adajacente[i][j].etat == 0){
                    printf("Sommet à O\n");
                }*/
            }
        }
    }

}


void freeGraph(matrice* Map){

    for (int i = 0; i < Map->nbSommet; i++) {
        free(Map->Adajacente[i]);
    }

    free(Map->Adajacente);
    free(Map);
}



//-------------------------------------------------------------------------//

int main(){
    srand(time(NULL)); 

    int taille = 50;
    matrice* Map = CreateGraph(&taille);

    if (Map == NULL) {
        printf("Erreur Création Map\n");
        return 0;
    }

    int sommet_depart = 0;

    afficherRoutes(Map);
    afficherCheminsAccessibles(Map, sommet_depart);
    afficherSommetsInaccessibles(Map, sommet_depart);
    faireSeisme(Map);
    //afficherRoutes(Map);
    afficherSommetsInaccessibles(Map, sommet_depart);

    freeGraph(Map);

    printf("\nFIN D'EXÉCUTION\n");
    return 0;
}
