#include <stdio.h>
#include <stdlib.h>

// DFS= Parcours en profondeur LowLink= La connexion vers l element le plus petit disponible
#define MAX_VERTICES 5  // Nombre maximum de sommets dans le graphe

// Structure representant un graphe
typedef struct Graph {
    int V;             // Nombre de sommets
    int **adj;         // Matrice d'adjacence
} Graph;

// Fonction pour creer un graphe
Graph* createGraph(int vertices) {
    Graph* g = (Graph*) malloc(sizeof(Graph));
    g->V = vertices;
    g->adj = (int**) malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        g->adj[i] = (int*) calloc(vertices, sizeof(int));  // Initialisation à 0 (aucune arete)
    }
    return g;
}

// Ajouter une arete dans le graphe
void addEdge(Graph* g, int u, int v) {
    g->adj[u][v] = 1;
}

// Fonction de DFS modifiee pour l'algorithme de Tarjan
void tarjanDFS(Graph* g, int u, int* index, int* lowLink, int* stack, int* onStack, int* top, int* currentIndex, int* finished) {
    index[u] = *currentIndex;
    lowLink[u] = *currentIndex;
    (*currentIndex)++;
    
    stack[(*top)++] = u;  // Empiler le sommet
    onStack[u] = 1;       // Marquer le sommet comme etant dans la pile

    // Parcours des voisins
    for (int v = 0; v < g->V; v++) {
        if (g->adj[u][v] == 1) {
            if (index[v] == -1) {
                tarjanDFS(g, v, index, lowLink, stack, onStack, top, currentIndex, finished);
                lowLink[u] = (lowLink[u] < lowLink[v]) ? lowLink[u] : lowLink[v];  // Mise à jour de lowLink
            } else if (onStack[v]) {
                lowLink[u] = (lowLink[u] < index[v]) ? lowLink[u] : index[v];  // Mise à jour de lowLink
            }
        }
    }

    // Si u est une racine de composante fortement connexe
    if (index[u] == lowLink[u]) {
        printf("Composante fortement connexe : ");
        int v;
        do {
            v = stack[--(*top)];
            onStack[v] = 0;
            printf("%d ", v);
            finished[v] = 1;  // Marquer le sommet comme termine
        } while (v != u);
        printf("\n");
    }
}

// Fonction pour trouver les composantes fortement connexes
void stronglyConnectedComponents(Graph* g) {
    int* index = (int*) malloc(g->V * sizeof(int));
    int* lowLink = (int*) malloc(g->V * sizeof(int));
    int* stack = (int*) malloc(g->V * sizeof(int));
    int* onStack = (int*) malloc(g->V * sizeof(int));
    int* finished = (int*) malloc(g->V * sizeof(int));  // Tableau pour marquer les sommets traites
    int top = 0;
    int currentIndex = 0;

    // Initialisation
    for (int i = 0; i < g->V; i++) {
        index[i] = -1;
        lowLink[i] = -1;
        onStack[i] = 0;
        finished[i] = 0;
    }

    // Appel de Tarjan pour chaque sommet non traite
    for (int i = 0; i < g->V; i++) {
        if (index[i] == -1) {
            tarjanDFS(g, i, index, lowLink, stack, onStack, &top, &currentIndex, finished);
        }
    }

    // Liberation de la memoire
    free(index);
    free(lowLink);
    free(stack);
    free(onStack);
    free(finished);
}

int main() {
    // Creation d'un graphe simple pour les tests
    Graph* g = createGraph(MAX_VERTICES);

    // Ajouter des aretes (exemple)
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    addEdge(g, 3, 4);
    addEdge(g, 4, 3);

    // Trouver et afficher les composantes fortement connexes
    stronglyConnectedComponents(g);

    // Liberation de la memoire du graphe
    for (int i = 0; i < MAX_VERTICES; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);

    return 0;
}
//j aime les pates
