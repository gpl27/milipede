/*!
 * Source file for object initialization functions
 */
#include "structs.h"
#include "raylib.h"
#include "graphics.h"

static Wall CheckCollisionBoundary(Rectangle pos);

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
        spiders[i].v.x = GetRandomValue(-SPIDER_V, SPIDER_V);
        spiders[i].v.y = GetRandomValue(-SPIDER_V, SPIDER_V);
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
    farmer->pTime = 0.0f;

    return;
}

void InitState(State *gameState) {
    gameState->lives = NUM_LIVES;
    gameState->shots = NUM_SHOTS;
    gameState->state = PLAYING;

    return;
}

void InitShots(Shot shots[]) {
    int i;

    for (i=0; i<NUM_SHOTS; i++) {
        shots[i].state = OFF;
        shots[i].pos.width = SHOT_SIZE;
        shots[i].pos.height = SHOT_SIZE;
    }

    return;
}

void InitGame(Game *game, Farmer *farmer, Shot shots[], Shroom shrooms[], Milipede milipedes[], Spider spiders[], State *gameState, MenuState *menuState) {
    game->farmer = farmer;
    game->shots = shots;
    game->shrooms = shrooms;
    game->milipedes = milipedes;
    game->spiders = spiders;
    game->gameState = gameState; 
    game->menuState = menuState;

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

    if (farmer->state == PARALYZED) {
        farmer->pTime += GetFrameTime();
        farmer->state = (farmer->pTime > FARMER_PTIME)? ALIVE : PARALYZED;
    }


    return;
}

void UpdateStates(Game *game) {
    // Instanciacao
    MenuState *menuState = game->menuState;
    State *gameState = game->gameState;

    
    // Switch Game and Menu States
    if (IsKeyPressed(KEY_P)) {
        gameState->state = (gameState->state)? PAUSED : PLAYING;
        *menuState = (*menuState == HIDDEN)? ACTIVE : HIDDEN;
    }

    // 
    switch (*menuState) {
        case EXIT_GAME_REQUEST:
            if (IsKeyPressed(KEY_S)) {
                *menuState = EXIT_GAME;
            }
            else if (IsKeyPressed(KEY_N)) {
                *menuState = ACTIVE;
            }
            break;
        case ACTIVE:
            if (IsKeyPressed(KEY_N)) {
                // TODO: resetar jogo
            } else if (IsKeyPressed(KEY_C)) {
                *menuState = LOAD;
            } else if (IsKeyPressed(KEY_S)) {
                *menuState = SAVE;
            } else if (IsKeyPressed(KEY_R)) {
                *menuState = RANKING;
            }
            break;
        case LOAD:
            // pede nome do jogo a ser carregado
            // carregar jogo
            break;
        case SAVE:
            // pedir nome do jogador
            // salvar jogo
            break;
        case RANKING:
            break;

    }

    return;
}


void UpdateSpiders(Spider spiders[]) {

    // TODO: check if all spiders are dead

    int i;
    for (i = 0; i < NUM_SPIDERS; i++) {
        // Check collision with walls
        if (spiders[i].state != DEAD) {
            switch(CheckCollisionBoundary(spiders[i].pos)) {
                case LEFT:
                case RIGHT:
                    spiders[i].v.x = -spiders[i].v.x;
                    break;
                case TOP:
                case BOTTOM:
                    spiders[i].v.y = -spiders[i].v.y;
                    break;
            }

            // Move spiders
            spiders[i].pos.x += spiders[i].v.x;
            spiders[i].pos.y += spiders[i].v.y;
        }

    }

    return; 
}

void UpdateMilipedes(Milipede milipedes[]) {

    // Check if milipede dead
        // if true, generate a new one

    // move milipede

    return;
}

void UpdateShots(Shot shots[], State *gameState, Farmer farmer) {
    int i;
    int lastShot = (NUM_SHOTS - gameState->shots) - 1;

    // Check for fired shot
    if (IsKeyPressed(KEY_SPACE)) {
        if (gameState->shots > 0 && farmer.state != PARALYZED) {
            // POssivel bugzin aqui kkk
            shots[++lastShot].pos.x = farmer.pos.x;
            shots[lastShot].pos.y = farmer.pos.y;
            shots[lastShot].state = ON;
            gameState->shots--;
        }
    }

    // Shot movement
    for(i = lastShot; ((i > lastShot - 10) && (i >= 0)); i--) {
        if (shots[i].state == ON) {
            shots[i].pos.y -= SHOT_V;
            if (CheckCollisionBoundary(shots[i].pos)) {
                shots[i].state = OFF;
            }
        }
    }
}

void CheckCollisions(Game *game) {
    // Instanciacao das variaveis do game que serao utilizadas
    Farmer *farmer = game->farmer;
    Shot *shots = game->shots;
    Shroom *shrooms = game->shrooms;
    Milipede *milipedes = game->milipedes;
    Spider *spiders = game->spiders;
    State *gameState = game->gameState; 

    
    // Onde o tiro bate
    int lastShot = (NUM_SHOTS - gameState->shots) - 1;
    int i;
    int j;
    for (i = lastShot; ((i > lastShot - 10) && (i >=0)); i--) {
        // Checa com shroom
        for (j = 0; j < NUM_SHROOMS; j++) {
            if (shrooms[j].state == PLANTED && CheckCollisionRecs(shots[i].pos, shrooms[j].pos)) {
                shrooms[j].state = HARVESTED;
                farmer->shrooms++;
                shots[i].state = OFF;
            }
        }
        // Checa com spider
        for (j = 0; j < NUM_SPIDERS; j++) {
            if (spiders[j].state != DEAD && CheckCollisionRecs(shots[i].pos, spiders[j].pos)) {
                spiders[j].state = DEAD;
                shots[i].state = OFF;
            }
        }
        // Checa com milipede
        // OBS.: DONT UOWK
        for (j = 0; j < NUM_MILIPEDES; j++) {
            if (CheckCollisionPointRec(milipedes[j].pos, shots[i].pos)) {
                milipedes[j].length--;
                shots[i].state = OFF;
            }
        }
    }

    // colisao farmer e aranha
    for (i = 0; i < NUM_SPIDERS; i++) {
        if (CheckCollisionRecs(spiders[i].pos, farmer->pos)) {
            // play oof sound

            if (farmer->state == ALIVE && gameState->lives > 0) {
                farmer->state = PARALYZED;
                farmer->pTime = 0.0f;
                gameState->lives--;
            }

        }
    }

    return;
}


static Wall CheckCollisionBoundary(Rectangle pos) {
    if (pos.x <= 0) {
        return LEFT;
    } else if (pos.x + pos.width >= SCREEN_WIDTH) {
        return RIGHT;
    } else if (pos.y <= MENU_HEIGHT) {
        return TOP;
    } else if (pos.y + pos.height >= MENU_HEIGHT + SCREEN_WIDTH) {
        return BOTTOM;
    } else {
        return NONE;
    }
}

