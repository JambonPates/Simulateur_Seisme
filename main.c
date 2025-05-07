#include <time.h>
#include "graph.h"



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
