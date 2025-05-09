#include <time.h>
#include "graph.h"

#define TailleGraph 10


//-------------------------------------------------------------------------//

int main(){
    srand(time(NULL)); 

    int taille = TailleGraph;
    matrice* Map = CreateGraph(&taille);

    if (Map == NULL) {
        printf("Erreur Création Map\n");
        return 0;
    }

    int sommet_depart = 0;

    //afficherRoutes(Map);
    //afficherCheminsAccessibles(Map, sommet_depart);
    //afficherSommetsInaccessibles(Map, sommet_depart);
    //parcoursEnProfondeur(Map, true);
    //faireSeisme(Map);
    //afficherRoutes(Map);
    //afficherSommetsInaccessibles(Map, sommet_depart);
    //parcoursEnProfondeur(Map, true);
    //parcoursEnLargeur(Map, true);
    identificationRoutesImportantes(Map);

    freeGraph(Map);

    printf("\nFIN D'EXÉCUTION\n");
    return 0;
}
