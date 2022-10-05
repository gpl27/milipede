/*!
 * Source file for graphics related functions
 */

#include "graphics.h"
#include "structs.h"
#include "raylib.h"


void DrawBackground(void) {
    char menuText[] = "ESC - Sair | C - Carregar | P - Pause | R - Ranking";
    int menuTextLength = MeasureText(menuText, FONT_SIZE);
    
    ClearBackground(MENU_COLOR);
    DrawRectangle(0, MENU_HEIGHT, SCREEN_WIDTH, SCREEN_WIDTH, BLACK);
    DrawText(menuText, (SCREEN_WIDTH - menuTextLength)/2, MENU_HEIGHT/4, FONT_SIZE, FONT_COLOR);
    DrawRectangle(0, (SCREEN_HEIGHT - MENU_HEIGHT - (SCREEN_WIDTH/4)), SCREEN_WIDTH, (SCREEN_WIDTH/4), DARKBROWN);

    return;
}

void DrawStats(State gameState, Farmer farmer) {
    const char *statsText = TextFormat("Score: %2d | Shrooms: %2d | Lives: %1d | Shots: %3d", farmer.shrooms, farmer.shrooms, gameState.lives, gameState.shots);
    int statsTextLength = MeasureText(statsText, FONT_SIZE);

    DrawText(statsText, (SCREEN_WIDTH - statsTextLength)/2, ((4*SCREEN_HEIGHT - 3*MENU_HEIGHT)/4), FONT_SIZE, FONT_COLOR);

    return;
}

// TODO: Add ShroomState switch
void DrawShrooms(Shroom shrooms[]) {
    int i;

    for (i = 0; i < NUM_SHROOMS; i++) {
        switch (shrooms[i].state) {
            case PLANTED:
                DrawRectangleRec(shrooms[i].pos, MAROON);
                break;
            case HARVESTED:
                DrawRectangleRec(shrooms[i].pos, GREEN);

        }
    }

    return;
}

// TODO: Add Milipede Length switch
void DrawMilipedes(Milipede milipedes[]) {
    int i, j;

    for (i = 0; i < NUM_MILIPEDES; i++) {
        for (j = 0; j < milipedes[i].length; j++) {
            switch(milipedes[i].state) {
                case ONSCENE:
                    DrawCircle((milipedes[i].pos.x + (j*2*MILIPEDE_SIZE)), milipedes[i].pos.y, MILIPEDE_SIZE, YELLOW);
                    break;
                default:
                    DrawCircle((milipedes[i].pos.x + (j*2*MILIPEDE_SIZE)), milipedes[i].pos.y, MILIPEDE_SIZE, ORANGE);
                    break;

            }
        }
    }

    return;
}

// TODO: add SpiderState switch
void DrawSpiders(Spider spiders[]) {
    int i;

    for (i = 0; i < NUM_SPIDERS; i++) {
        switch (spiders[i].state) {
            case DEAD:
                DrawRectangleRec(spiders[i].pos, RED);
                break;
            default:
                DrawRectangleRec(spiders[i].pos, DARKPURPLE);
                break;
        }
    }

    return;
}

void DrawFarmer(Farmer farmer) {
    switch (farmer.state) {
        case ALIVE:
            DrawRectangleRec(farmer.pos, FONT_COLOR);
            break;
        case PARALYZED:
            DrawRectangleRec(farmer.pos, RED);
            break;
    }

    return;
}

void DrawExitWindowRequest(void) {
    char exitText[] = "Você tem certeza que deseja sair? [S/N]";
    int exitTextLength = MeasureText(exitText, FONT_SIZE);
    DrawRectangle(0, (SCREEN_HEIGHT - SCREEN_WIDTH/4)/2, SCREEN_WIDTH, SCREEN_WIDTH/4, MENU_COLOR);
    DrawText(exitText, (SCREEN_WIDTH - exitTextLength)/2, (SCREEN_HEIGHT - FONT_SIZE)/2, FONT_SIZE, FONT_COLOR);

    return;
}

void DrawMenu(MenuState menuState) {
    char line0[] = "<N> Novo Jooj    <R> Ranking";
    char line1[] = "<C> Carregar Jooj    <P> Sair do Menu";
    char line2[] = "<S> Salvar Jooj    <ESC> Sair do Jooj";
    int line0Length = MeasureText(line0, FONT_SIZE);
    int line1Length = MeasureText(line1, FONT_SIZE);
    int line2Length = MeasureText(line2, FONT_SIZE);
    int padding = (SCREEN_WIDTH/2 - 4*FONT_SIZE)/5;

    DrawRectangle(0, (SCREEN_HEIGHT - SCREEN_WIDTH/2)/2, SCREEN_WIDTH, SCREEN_WIDTH/2, MENU_COLOR);

    switch (menuState) {
        case ACTIVE:
            DrawText("MENU", (SCREEN_WIDTH - 100)/2, (SCREEN_HEIGHT - SCREEN_WIDTH/2)/2 + padding, FONT_SIZE, FONT_COLOR);
            DrawText(line0, (SCREEN_WIDTH - line0Length)/2, (SCREEN_HEIGHT - SCREEN_WIDTH/2)/2 + 2*padding, FONT_SIZE, FONT_COLOR);
            DrawText(line1, (SCREEN_WIDTH - line1Length)/2, (SCREEN_HEIGHT - SCREEN_WIDTH/2)/2 + 3*padding, FONT_SIZE, FONT_COLOR);
            DrawText(line2, (SCREEN_WIDTH - line2Length)/2, (SCREEN_HEIGHT - SCREEN_WIDTH/2)/2 + 4*padding, FONT_SIZE, FONT_COLOR);

            break;
        case LOAD:
            DrawText("LOAD", (SCREEN_WIDTH - 100)/2, (SCREEN_HEIGHT - FONT_SIZE)/2, FONT_SIZE, FONT_COLOR);
            break;
        case SAVE:
            DrawText("SAVE", (SCREEN_WIDTH - 100)/2, (SCREEN_HEIGHT - FONT_SIZE)/2, FONT_SIZE, FONT_COLOR);
            break;
    }

    return;
}

void DrawShots(Shot shots[], int shotsLeft) {
    int i;
    int lastShot = (NUM_SHOTS - shotsLeft) - 1;
    
    for(i = lastShot; ((i > lastShot - 10) && (i >= 0)); i--) {
        if (shots[i].state == ON) {
            DrawRectangleRec(shots[i].pos, WHITE);
        }
    }

    return;
}