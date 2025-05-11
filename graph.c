#include "graph.h"

//-------------------------------------------------------------------------//

matrice* CreateGraph(int* size){
    // Création et remplissage du graph 

    //Création
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
    
    // Ajout des routes
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
        //Géneration aléatoire des informations

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
    // Affiche toutes les routes du graph

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


void afficherSommetsInaccessibles(matrice* Map){
    // Affiche tous les sommets inaccessibles

    printf("\n--- Sommets inaccessibles depuis le sommet 0 ---\n");

    int inaccessible = 1;

    for (int i = 1; i < Map->nbSommet; i++){

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
    // Fonction qui détruit les routes de façon aléatoire

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


void ComposantesFortementConnexes(matrice* Map){

    int n = Map->nbSommet;

    bool* visite = calloc(n, sizeof(bool));
    int* pile = malloc(n * sizeof(int));
    int sommetPile = 0;

    if (!visite || !pile){

        printf("Erreur d'allocation mémoire\n");
        exit(-1);

    }


    // --------------------- 1er DFS : remplir la pile par ordre de fin ---------------------

    for (int v = 0; v < n; v++){

        if (!visite[v]){
            
            int* stack = malloc(n * sizeof(int));
            int top = 0;
            int* next = calloc(n, sizeof(int));

            stack[top] = v;
            top += 1;

            while (top > 0){

                int u = stack[top - 1];

                if (!visite[u]){

                    visite[u] = true;
                }

                bool pushed = false;

                for (; next[u] < n; next[u]++){

                    int w = next[u];

                    if (Map->Adajacente[u][w].existe && Map->Adajacente[u][w].etat > 0 && !visite[w]){

                        stack[top] = w;
                        top+= 1;
                        pushed = true;
                        break;

                    }
                }

                if (!pushed){

                    pile[sommetPile] = u;
                    sommetPile++;
                    top--;

                }
            }

            free(stack);
            free(next);
        }
    }

    // --------------------- Transposer du graphe ---------------------
    route** transpose = malloc(n * sizeof(route*));

    for (int i = 0; i < n; i++){

        transpose[i] = malloc(n * sizeof(route));

        for (int j = 0; j < n; j++){

            transpose[i][j].existe = Map->Adajacente[j][i].existe;
            transpose[i][j].etat = Map->Adajacente[j][i].etat;
        }

    }

    // --------------------- 2e DFS sur le graphe transposé ---------------------
    for (int i = 0; i < n; i++){

        visite[i] = false;
    } 

    printf("\n--- Composantes Fortement Connexes (Kosaraju) ---\n");

    while (sommetPile > 0){

        sommetPile--;
        int v = pile[sommetPile];

        if (!visite[v]){

            int* stack = malloc(n * sizeof(int));
            int top = 0;

            stack[top] = v;
            top++;
            visite[v] = true;

            printf("CFC : ");

            while (top > 0){

                top--;
                int u = stack[top];

                printf("%d ", u);

                for (int w = 0; w < n; w++){

                    if (transpose[u][w].existe && transpose[u][w].etat > 0 && !visite[w]) {
                        stack[top] = w;
                        top++;
                        visite[w] = true;
                    }

                }
            }

            printf("\n");
            free(stack);

        }
    }

    
    for (int i = 0; i < n; i++){ 

        free(transpose[i]);

    }

    free(transpose);
    free(visite);
    free(pile);

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
    pile[sommetTop] = 0;
    sommetTop++; 

    printf("\n--- Parcours en profondeur ---\n");

    while (sommetTop > 0){

        sommetTop--;
        int courant = pile[sommetTop]; 

        if (!visites[courant]){

            visites[courant] = true;
            //printf("sommet %d\n", courant);

            for (int i = Map->nbSommet - 1; i >= 0; i--) {
                if (Map->Adajacente[courant][i].existe && Map->Adajacente[courant][i].etat > 0 && !visites[i]) {
                    pile[sommetTop++] = i; 
                }
            }
        }

    }

    if (afficherSommetInaccessible){
        // Affichage si demandé

        for (int i = 0; i < Map->nbSommet; i++){
            if (visites[i] == false){
                printf("Le sommet %d n'est pas accessiblle depuis le sommet début\n", i);
            }
        }
    }

    free(visites);
    free(pile);
}


void parcoursEnLargeur(matrice* Map, bool afficherArcs){
    // Parcours en largeur, pour afficher les arcs parcourus mettre le bool à True

    bool* visites = malloc(Map->nbSommet * sizeof(bool));

    if (visites == NULL){

        printf("Erreur d'allocation pour visites\n");
        exit(-1);
    }

    for (int i = 0; i < Map->nbSommet; i++){

        visites[i] = false;

    }

    int* file = malloc(Map->nbSommet * sizeof(int));

    if (file == NULL){

        printf("Erreur d'allocation pour file\n");
        free(visites);
        exit(-1);

    }

    int debut = 0;
    int fin = 0;

    file[fin] = 0;  
    fin++;
    visites[0] = true;

    printf("\n--- Parcours en largeur ---\n");

    while (debut < fin){

        int courant = file[debut];
        debut++;
        //printf("Sommet %d\n", courant);

        for (int i = 0; i < Map->nbSommet; i++){

            if (Map->Adajacente[courant][i].existe && Map->Adajacente[courant][i].etat > 0 && Map->Adajacente[courant][i].capacite > 0 && !visites[i]){

                if (afficherArcs){
                    //affichage des arcs si demandé

                    printf("Arc parcouru : %d -> %d\n", courant, i);
                
                }

                file[fin] = i;  
                fin++;
                visites[i] = true;

            }
        }
    }


    free(visites);
    free(file);

}


// Algo de Chu-Liu/Edmonds
void identificationRoutesImportantes(matrice* Map){

    int* parents = malloc(Map->nbSommet * sizeof(int));

    for (int i = 0; i < Map->nbSommet; i++){

        if (i == 0){
            parents[i] = -1;
            continue;
        }

        int minPoids = 100;
        int parent = -1;
        
        // On cherche pour chaque sommet l'arc entrant avec le poids le plus faible et on l'enregistre
        for (int j = 0; j < Map->nbSommet; j++){

            if (Map->Adajacente[j][i].existe && Map->Adajacente[j][i].etat > 0 && Map->Adajacente[j][i].distance < minPoids){

                minPoids = Map->Adajacente[j][i].distance;
                parent = j;

            }

        }
        parents[i] = parent;

    }


    printf("Arborescence de poids minimal :\n");

    for (int i = 0; i < Map->nbSommet; i++){

        if (parents[i] != -1){
            printf("%d -> %d (poids : %d)\n", parents[i], i, Map->Adajacente[parents[i]][i].distance);
        }

    }

    free(parents);    
    
}


void ResetSurbrillance(matrice* Map){
    // Reset toutes les arretes à surbrillance = False

    for (int i = 0; i < Map->nbSommet; i++){
        
        for (int j = 0; j < Map->nbSommet; j++){

            Map->Adajacente[i][j].surbrillance = false;
        }
    }
}


void freeGraph(matrice* Map){
    //Libération de toutes les allocations dynamiques du graph

    for (int i = 0; i < Map->nbSommet; i++){

        free(Map->Adajacente[i]);
        
    }

    free(Map->Adajacente);
    free(Map);

}