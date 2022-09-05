/*!
 * Source file for graphics related functions
 */

#include "graphics.h"
#include "structs.h"
#include "raylib.h"


void DrawBackground(void) {
    char menuText[] = "ESC - Sair | C - Carregar | P - Pause | R - Ranking";
    int menuTextLength = MeasureText(menuText, FONT_SIZE);
    
    ClearBackground(DARKBLUE);
    DrawRectangle(0, MENU_HEIGHT, SCREEN_WIDTH, SCREEN_WIDTH, BLACK);
    DrawText(menuText, (SCREEN_WIDTH - menuTextLength)/2, MENU_HEIGHT/4, FONT_SIZE, WHITE);
    DrawRectangle(0, (SCREEN_HEIGHT - MENU_HEIGHT - (SCREEN_WIDTH/4)), SCREEN_WIDTH, (SCREEN_WIDTH/4), DARKBROWN);

    return;
}

void DrawStats(State gameState, Farmer farmer) {
    const char *statsText = TextFormat("Score: %2d | Shrooms: %2d | Lives: %1d | Shots: %3d", farmer.shrooms, farmer.shrooms, gameState.lives, gameState.shots);
    int statsTextLength = MeasureText(statsText, FONT_SIZE);

    DrawText(statsText, (SCREEN_WIDTH - statsTextLength)/2, ((4*SCREEN_HEIGHT - 3*MENU_HEIGHT)/4), FONT_SIZE, WHITE);

    return;
}

// TODO: Add ShroomState switch
void DrawShrooms(Shroom shrooms[]) {
    int i;

    for (i = 0; i < NUM_SHROOMS; i++) {
        DrawRectangleRec(shrooms[i].pos, MAROON);
    }

    return;
}

// TODO: Add Milipede Length switch
void DrawMilipedes(Milipede milipedes[]) {
    int i, j;

    for (i = 0; i < NUM_MILIPEDES; i++) {
        for (j = 0; j < milipedes[i].length; j++) {
            DrawCircle((milipedes[i].pos.x + (j*2*MILIPEDE_SIZE)), milipedes[i].pos.y, MILIPEDE_SIZE, YELLOW);
        }
    }

    return;
}

// TODO: add SpiderState switch
void DrawSpiders(Spider spiders[]) {
    int i;

    for (i = 0; i < NUM_SPIDERS; i++) {
        DrawRectangleRec(spiders[i].pos, DARKPURPLE);
    }

    return;
}

void DrawFarmer(Farmer farmer) {
    DrawRectangleRec(farmer.pos, WHITE);

    return;
}

void DrawExitWindowRequest(void) {
    char exitText[] = "Você tem certeza que deseja sair? [S/N]";
    int exitTextLength = MeasureText(exitText, FONT_SIZE);
    DrawRectangle(0, (SCREEN_HEIGHT - SCREEN_WIDTH/4)/2, SCREEN_WIDTH, SCREEN_WIDTH/4, DARKBLUE);
    DrawText(exitText, (SCREEN_WIDTH - exitTextLength)/2, (SCREEN_HEIGHT - FONT_SIZE)/2, FONT_SIZE, WHITE);

    return;
}
