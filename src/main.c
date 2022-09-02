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


int main(void) {

    // ------------------------------
    // Inicializacao
    // ------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Milipede");
    SetTargetFPS(60);

    // Inicializar Fazendeiro: Nome, numero de cogumelos colhidos, paralisado/movimento/morto
    Farmer player;
    InitFarmer(&player);
    // Inicializar os Cogumelos: vetor de typedef Cogumelo
    Shroom shrooms[NUM_SHROOMS];
    InitShrooms(shrooms);
    // Inicializar as Milipedes
    Milipede milipedes[NUM_MILIPEDES];
    InitMilipedes(milipedes);
    // Inicializar as Aranhas
    Spider spiders[NUM_SPIDERS];
    InitSpiders(spiders);
    // Inicializar o Status do jogo
    State gameState;
    InitState(&gameState);

    // Funcao com loop apenas do Menu inicial


    // Main Game Loop
    while (!WindowShouldClose()) {
        // ------------------------------
        // Update
        // ------------------------------

            // UpdateSpiders
            // UpdateMilipedes
            // UpdateFarmer
            UpdateFarmer(&player);




        // ------------------------------
        // Draw
        // ------------------------------
        BeginDrawing();

            DrawBackground();
            DrawStats(gameState, player);
            DrawShrooms(shrooms);
            DrawMilipedes(milipedes);
            DrawSpiders(spiders);
            DrawFarmer(player);

        EndDrawing();
    }


    // ------------------------------
    // Desinicializacao
    // ------------------------------
    CloseWindow();


    return 0;
}