#include "raylib.h"
#include "graph.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NB_SOMMETS 12
#define RAYON 20
#define TAILLE_FENETRE 900
void DessinerRoute(Vector2 a, Vector2 b, route r) {
    if (!r.existe) return;

    Color couleur;
    if (r.etat >= 3) couleur = DARKGREEN;
    else if (r.etat == 2) couleur = ORANGE;
    else if (r.etat == 1) couleur = RED;
    else couleur = LIGHTGRAY;

    DrawLineEx(a, b, 2.0f, couleur);
}

void DessinerSommet(Vector2 position, int indice, bool survole) {
    DrawCircleV(position, RAYON, survole ? GOLD : SKYBLUE);
    DrawCircleLines(position.x, position.y, RAYON, DARKBLUE);
    DrawText(TextFormat("%d", indice), position.x - 5, position.y - 10, 20, BLACK);
}
int main() {
    srand(time(NULL));

    InitWindow(TAILLE_FENETRE, TAILLE_FENETRE, "Graphe Interactif avec Raylib");
    SetTargetFPS(60);

    int taille = NB_SOMMETS;
    matrice* carte = CreateGraph(&taille);

    Vector2 positions[NB_SOMMETS];
    float pasAngle = 2 * PI / taille;
    Vector2 centre = { TAILLE_FENETRE / 2.0f, TAILLE_FENETRE / 2.0f };
    float rayonDisque = 300;

    for (int i = 0; i < taille; i++) {
        positions[i].x = centre.x + cosf(i * pasAngle) * rayonDisque;
        positions[i].y = centre.y + sinf(i * pasAngle) * rayonDisque;
    }
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_S)) {
            faireSeisme(carte);
        }
        if (IsKeyPressed(KEY_R)) {
            freeGraph(carte);
            carte = CreateGraph(&taille);
        }

        Vector2 souris = GetMousePosition();
        int sommetSurvole = -1;
        for (int i = 0; i < taille; i++) {
            if (CheckCollisionPointCircle(souris, positions[i], RAYON)) {
                sommetSurvole = i;
                break;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                DessinerRoute(positions[i], positions[j], carte->Adajacente[i][j]);
            }
        }
        for (int i = 0; i < taille; i++) {
            DessinerSommet(positions[i], i, i == sommetSurvole);
        }
        if (sommetSurvole != -1) {
            int yTexte = 20;
            DrawText(TextFormat("Sommet %d", sommetSurvole), 20, yTexte, 20, BLACK);
            yTexte += 30;
            for (int j = 0; j < taille; j++) {
                if (carte->Adajacente[sommetSurvole][j].existe) {
                    route r = carte->Adajacente[sommetSurvole][j];
                    DrawText(TextFormat("-> %d | dist: %d | état: %d | capacité: %d", j, r.distance, r.etat, r.capacite),
                        20, yTexte, 18, DARKGRAY);
                    yTexte += 22;
                }
            }
        }
        DrawText("[S] Séisme", 700, 20, 20, DARKGRAY);
        DrawText("[R] Réinitialiser", 700, 50, 20, DARKGRAY);
        DrawText("Survolez un sommet pour voir les routes", 20, TAILLE_FENETRE - 30, 18, GRAY);

        EndDrawing();
    }

    freeGraph(carte);
    CloseWindow();
    return 0;
}
