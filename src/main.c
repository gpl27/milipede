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
    bool exitWindow = false;
    // ------------------------------
    // Inicializacao
    // ------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Milipede");
    SetTargetFPS(60);

    // Inicializar Fazendeiro: Nome, numero de cogumelos colhidos, paralisado/movimento/morto
    Farmer farmer;
    InitFarmer(&farmer);
    // Inicializar Tiros
    Shot shots[NUM_SHOTS];
    InitShots(shots);
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
    // Inicializar o Status do Menu
    MenuState menuState = HIDDEN;



    // Funcao com loop apenas do Menu inicial


    // Main Game Loop
    while (menuState != EXIT_GAME) {


        // ------------------------------
        // Update
        // ------------------------------
            
        UpdateStates(&gameState, &menuState);    
        
        // windowshouldclose
        if (WindowShouldClose()) {
            menuState = EXIT_GAME_REQUEST;
            gameState.state = PAUSED;
        } 
        // gamestate == playing
        if (gameState.state == PLAYING) {
            // UpdateSpiders
            UpdateSpiders(spiders);
            // UpdateMilipedes
            UpdateMilipedes(milipedes);
            // UpdateFarmer
            UpdateFarmer(&farmer);
            // UpdateShots
            UpdateShots(shots, &gameState, farmer);
            // Check Collisions
            CheckCollisions(&gameState, &farmer, shots, shrooms, milipedes, spiders);
        } 
            

        // ------------------------------
        // Draw
        // ------------------------------
        BeginDrawing();

            DrawBackground();
            DrawStats(gameState, farmer);
            DrawShrooms(shrooms);
            DrawMilipedes(milipedes);
            DrawSpiders(spiders);
            DrawFarmer(farmer);  
            DrawShots(shots, gameState.shots);
              
            // gamestate == paused
            if (gameState.state == PAUSED) {
                DrawMenu(menuState);
            }    
               
            if (menuState == EXIT_GAME_REQUEST) {
                DrawExitWindowRequest();
            }      

        EndDrawing();
    }


    // ------------------------------
    // Desinicializacao
    // ------------------------------
    CloseWindow();


    return 0;
}