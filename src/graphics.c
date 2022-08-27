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
}

void DrawFarmer(Farmer farmer) {
    DrawRectangleRec(farmer.pos, WHITE);
}