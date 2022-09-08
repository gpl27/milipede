/*!
 * Source file for object initialization functions
 */

#include "structs.h"
#include "raylib.h"
#include "graphics.h"


/*
 * Initialization functions
 */
void InitShrooms(Shroom shroom[]) {
    int i;

    for (i = 0; i < NUM_SHROOMS; i++) {
        shroom[i].pos.x = GetRandomValue(0, (SCREEN_WIDTH - SHROOM_SIZE));
        shroom[i].pos.y = GetRandomValue(MENU_HEIGHT, (SCREEN_WIDTH/4*3));
        shroom[i].pos.width = SHROOM_SIZE;
        shroom[i].pos.height = SHROOM_SIZE;
        shroom[i].state = PLANTED;
    }

    return;
}

void InitMilipedes(Milipede milipedes[]) {
    int i;

    for (i = 0; i < NUM_MILIPEDES; i++) {
        milipedes[i].length = GetRandomValue(4, 8);
        milipedes[i].pos.x = GetRandomValue(0, (SCREEN_WIDTH - SHROOM_SIZE));
        milipedes[i].pos.y = GetRandomValue(MENU_HEIGHT, (SCREEN_WIDTH/4*3));
        milipedes[i].v.x = MILIPEDE_V;
        milipedes[i].v.y = 0;
    }

    return;
}

void InitSpiders(Spider spiders[]) {
    int i;

    for (i = 0; i < NUM_SPIDERS; i++) {
        spiders[i].pos.x = GetRandomValue(0, (SCREEN_WIDTH - SHROOM_SIZE));
        spiders[i].pos.y = GetRandomValue(MENU_HEIGHT, (SCREEN_WIDTH/4*3));
        spiders[i].pos.width = SPIDER_SIZE;
        spiders[i].pos.height = SPIDER_SIZE;
        spiders[i].state = ONSCENE;
        // TODO: define spider velocity
    }

    return;
}

void InitFarmer(Farmer *farmer) {
    farmer->pos.x = SCREEN_WIDTH/2;
    farmer->pos.y = (SCREEN_HEIGHT - (SCREEN_WIDTH/8) - MENU_HEIGHT);
    farmer->pos.width = FARMER_SIZE;
    farmer->pos.height = FARMER_SIZE;
    farmer->shrooms = 0;
    farmer->state = ALIVE;

    return;
}

void InitState(State *gameState) {
    gameState->lives = 3;
    gameState->shots = 200;
    gameState->state = PLAYING;

    return;
}

/*
 * Update Functions
 */
void UpdateFarmer(Farmer *farmer) {
    // Movement
    if (IsKeyDown(KEY_RIGHT) && ((farmer->pos.x + farmer->pos.width) < SCREEN_WIDTH)) {
        farmer->pos.x += FARMER_V;
    }
    if (IsKeyDown(KEY_LEFT) && (farmer->pos.x > 0)) {
        farmer->pos.x -= FARMER_V;
    } 
    if (IsKeyDown(KEY_UP) && (farmer->pos.y > (SCREEN_HEIGHT - MENU_HEIGHT - SCREEN_WIDTH/4))) {
        farmer->pos.y -= FARMER_V;
    } 
    if (IsKeyDown(KEY_DOWN) && ((farmer->pos.y + farmer->pos.height) < (SCREEN_HEIGHT - MENU_HEIGHT))) {
        farmer->pos.y += FARMER_V;
    }

    return;
}

void UpdateState(State *gameState) {
    if (IsKeyPressed(KEY_P)) {
        gameState->state = (gameState->state)? PAUSED : PLAYING;
    }


    return;
}

void UpdateMenuState(MenuState *menuState) {

    if (*menuState == EXIT_GAME_REQUEST) {
        if (IsKeyPressed(KEY_S)) {
            *menuState = EXIT_GAME;
        }
        else if (IsKeyPressed(KEY_N)) {
            *menuState = ACTIVE;
        }
    } else {

        if (IsKeyPressed(KEY_N)) {
            // TODO: resetar jogo
        } else if (IsKeyPressed(KEY_C)) {
            *menuState = LOAD;
        } else if (IsKeyPressed(KEY_S)) {
            *menuState = SAVE;
        } else if (IsKeyPressed(KEY_R)) {
            *menuState = RANKING;
        }

    }

    return;
}

