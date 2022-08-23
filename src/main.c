/*!
 * Milipede
 *
 * Eduardo Stuani & Gustavo Lacroix
 * 
 * Requisitos nao alcancados:
 * 
 */

#include <stdio.h>
#include "raylib.h"
#include "structs.h"
#include "graphics.h"

#define FONT_SIZE 20
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT (SCREEN_WIDTH + 3*FONT_SIZE)

int main(void) {

    // ------------------------------
    // Inicializacao
    // ------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Milipede");
    SetTargetFPS(60);

    // Inicializar Fazendeiro: Nome, numero de cogumelos colhidos, paralisado/movimento/morto
    // Inicializar os Cogumelos: vetor de typedef Cogumelo
    // Inicializar as Milipedes
    // Inicializar as Aranhas
    // Inicializar o Status do jogo

    // Funcao com loop apenas do Menu inicial


    // Main Game Loop
    while (!WindowShouldClose()) {
        // ------------------------------
        // Update
        // ------------------------------





        // ------------------------------
        // Draw
        // ------------------------------
        BeginDrawing();

            DrawBackground(SCREEN_WIDTH, SCREEN_HEIGHT, FONT_SIZE);

        EndDrawing();
    }


    // ------------------------------
    // Desinicializacao
    // ------------------------------
    CloseWindow();


    return 0;
}