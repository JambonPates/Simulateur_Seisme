#include "graph.h"

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

        if (Map->Adajacente[depart][i].existe && Map->Adajacente[depart][i].etat != 0 && Map->Adajacente[depart][i].capacite > 0){

            printf("  -> %d (Distance: %d, Capacité: %d, etat: %d)\n", i, Map->Adajacente[depart][i].distance, Map->Adajacente[depart][i].capacite, Map->Adajacente[depart][i].etat);
        }
    }

}

void afficherSommetsInaccessibles(matrice* Map, int depart){

    printf("\n--- Sommets inaccessibles depuis le sommet %d ---\n", depart);

    int inaccessible = 1;

    for (int i = 1; i < Map->nbSommet; i++) {
        for (int j = 0; j < i; j++){
            if (Map->Adajacente[i][j].existe != 0 || Map->Adajacente[i][j].etat > 0){
                inaccessible = 0;
            }
        }
        if (inaccessible){
            printf("Le Sommet %d est inaccessible\n", i);
            inaccessible = 1;
        }
        
    }
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


void parcoursEnProfondeur(matrice* Map, bool afficherSommetInaccessible){

    bool* visites = malloc(Map->nbSommet * sizeof(bool));

    if (visites == NULL){
        printf("Erreur d'allocation tableau marquage\n");
        exit(-1);
    }

    for (int i = 0; i < Map->nbSommet; i++){
        visites[i] = false;
    }

    int* pile = malloc(Map->nbSommet * sizeof(int));

    if (pile == NULL){
        printf("Erreur d'allocation pile\n");
        free(visites);
        exit(-1);
    }

    int sommetTop = 0;  
    pile[sommetTop++] = 0; 

    printf("\n--- Parcours en profondeur ---\n");

    while (sommetTop > 0){

        int courant = pile[--sommetTop]; 

        if (!visites[courant]){

            visites[courant] = true;
            //printf("sommet %d\n", courant);

            for (int i = Map->nbSommet - 1; i >= 0; i--) {
                if (Map->Adajacente[courant][i].existe && Map->Adajacente[courant][i].etat > 0 && !visites[i]) {
                    pile[sommetTop++] = i; // empile le voisin
                }
            }
        }

    }

    if (afficherSommetInaccessible){

        for (int i = 0; i < Map->nbSommet; i++){
            if (visites[i] == false){
                printf("Le sommet %d n'est pas accessiblle depuis le sommet début\n", i);
            }
        }
    }

    free(visites);
    free(pile);
}


void parcoursEnLargeur(matrice* Map){


}


void identificationRoutesImportantes(matrice* Map){

}


void freeGraph(matrice* Map){

    for (int i = 0; i < Map->nbSommet; i++) {
        free(Map->Adajacente[i]);
    }

    free(Map->Adajacente);
    free(Map);
}