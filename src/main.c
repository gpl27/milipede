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
    bool exitWindowRequested = false;
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
    // Inicializar o Status do Menu
    MenuState menuState = HIDDEN;


    // Funcao com loop apenas do Menu inicial


    // Main Game Loop
    while (!exitWindow) {


        // ------------------------------
        // Update
        // ------------------------------
            
            UpdateState(&gameState);    
            
            // windowshouldclose
            if (WindowShouldClose()) {
                exitWindowRequested = true;
                gameState.state = PAUSED;
            } 
            // gamestate == playing
            if (gameState.state == PLAYING) {
                // UpdateSpiders
                // UpdateMilipedes
                // UpdateFarmer
                UpdateFarmer(&player);


            } 
            // gamestate == paused
            else if (gameState.state == PAUSED) {
                //TODO
                //UpdateMenu(&menuState);
                
                if (exitWindowRequested) {
                    if (IsKeyPressed(KEY_S)) {
                        exitWindow = true;
                    }
                    else if (IsKeyPressed(KEY_N)) {
                        exitWindowRequested = false;
                        if (!menuState) {
                            gameState.state = PLAYING; 
                        } 
                    }
                }          
            }

            

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
              
            // gamestate == paused
            if (gameState.state == PAUSED) {
                DrawMenu();
            }    
               
            if (exitWindowRequested) {
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