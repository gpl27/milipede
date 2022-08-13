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
// #include "mobs.h"
//      Contem as definicoes de dados

#define SCREEN_WIDTH 360
#define SCREEN_HEIGHT 640
#define FONT_SIZE 10
#define BARRA_H (FONT_SIZE*2)

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

            ClearBackground(DARKGRAY);
            DrawRectangle(0, 0, SCREEN_WIDTH, BARRA_H, BLACK);
            DrawRectangle(0, (SCREEN_HEIGHT - BARRA_H), SCREEN_WIDTH, BARRA_H, BLACK);

        EndDrawing();
    }


    // ------------------------------
    // Desinicializacao
    // ------------------------------
    CloseWindow();


    return 0;
}