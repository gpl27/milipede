/*!
 * Source file for object initialization functions
 */
#include "structs.h"
#include "raylib.h"
#include "graphics.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Wall CheckCollisionBoundary(Rectangle pos);

void GetPlayerName(char name[]);
static void LoadGame(char name[], Game *game);
static void SaveGame(char name[], Game game);


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
        milipedes[i].length = GetRandomValue(4, 10);
        milipedes[i].pos.x = GetRandomValue(0, (SCREEN_WIDTH - SHROOM_SIZE));
        milipedes[i].pos.y = GetRandomValue(MENU_HEIGHT, (SCREEN_WIDTH/4*3));
        milipedes[i].pos.width = 2*MILIPEDE_SIZE;
        milipedes[i].pos.height = 2*MILIPEDE_SIZE;
        milipedes[i].v.x = MILIPEDE_V;
        milipedes[i].v.y = 0;
        milipedes[i].pTime = 0.0f;
        milipedes[i].state = ONSCENE;
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
        spiders[i].pTime = 0.0f;
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
    strcpy(gameState->name, "\0");
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

    switch (*menuState) {
        case HIDDEN:
            if (IsKeyPressed(KEY_P)) {
                gameState->state = PAUSED;
                *menuState = ACTIVE;
            }
            break;
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
            } else if (IsKeyPressed(KEY_P)) {
                gameState->state = PLAYING;
                *menuState = HIDDEN;
            }
            break;
        case LOAD:
            // pede nome do jogo a ser carregado
            // carregar jogo
            if (IsKeyPressed(KEY_ENTER)) {
                LoadGame(gameState->name, game);
                *menuState = ACTIVE;
            }
            GetPlayerName(gameState->name);
            break;
        case SAVE:
            // pedir nome do jogador
            if (IsKeyPressed(KEY_ENTER)) {
                SaveGame(gameState->name, *game);
                *menuState = ACTIVE;
            }
            GetPlayerName(gameState->name);
            break;
        case RANKING:
            if (IsKeyPressed(KEY_B)) {
                *menuState = ACTIVE;
            }
            break;

    }

    return;
}

void GetPlayerName(char name[]) {
    int letterCount = strlen(name);
    int key = GetKeyPressed(); 

    if (key >= 32 && key <= 125) {
        name[letterCount] = (char) key;
        letterCount++;
        name[letterCount] = '\0';
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        letterCount -= 2;
        letterCount = (letterCount < 0)? 0 : letterCount;
        name[letterCount] = '\0';
    }

    return;
}

void UpdateSpiders(Spider spiders[]) {
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

        if (spiders[i].state == DEAD) {
            spiders[i].pTime += GetFrameTime();
            if (spiders[i].pTime > DEATH_TIME) {
                spiders[i].pos.x = GetRandomValue(0, (SCREEN_WIDTH - SHROOM_SIZE));
                spiders[i].pos.y = GetRandomValue(MENU_HEIGHT, (SCREEN_WIDTH/4*3));
                spiders[i].state = ONSCENE;
                spiders[i].v.x = GetRandomValue(-SPIDER_V, SPIDER_V);
                spiders[i].v.y = GetRandomValue(-SPIDER_V, SPIDER_V);
                spiders[i].pTime = 0.0f;
            }
        }

    }

    return; 
}

void UpdateMilipedes(Milipede milipedes[]) {

    int i;
    for (i = 0; i < NUM_MILIPEDES; i++) {

        if (milipedes[i].state == DEAD) {
            milipedes[i].pTime += GetFrameTime();
            if (milipedes[i].pTime > DEATH_TIME) {
                milipedes[i].length = GetRandomValue(4, 10);
                milipedes[i].pos.x = GetRandomValue(0, (SCREEN_WIDTH - SHROOM_SIZE));
                milipedes[i].pos.y = GetRandomValue(MENU_HEIGHT, (SCREEN_WIDTH/4*3));
                milipedes[i].pTime = 0.0f;
                milipedes[i].state = ONSCENE;
            }
            
        }

        if (milipedes[i].state == STUNNED) {
            milipedes[i].pTime += GetFrameTime();
            milipedes[i].state = (milipedes[i].pTime > STUN_TIME)? ONSCENE : STUNNED;
        }

        if (milipedes[i].state == ONSCENE) {
            switch (CheckCollisionBoundary(milipedes[i].pos)) {
                case LEFT:
                case RIGHT:
                    milipedes[i].v.x = -milipedes[i].v.x;
                    break;
            }
            milipedes[i].pos.x += milipedes[i].v.x;
        }


    }

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
        if (shots[i].state == ON) {

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
                    spiders[j].pTime = 0.0f;
                    shots[i].state = OFF;
                }
            }
            // Checa com milipede
            for (j = 0; j < NUM_MILIPEDES; j++) {
                if (CheckCollisionRecs(milipedes[j].pos, shots[i].pos)) {
                    if (milipedes[j].state == ONSCENE) {
                        milipedes[j].length--;
                        milipedes[j].state = (milipedes[j].length == 0)? DEAD: STUNNED;
                        milipedes[j].pTime = 0.0f;
                        shots[i].state = OFF;
                    }
                }
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

static void LoadGame(char name[], Game *game) {
    FILE *f;

    char fileName[STR_LEN];
    strcpy(fileName, name);
    strcat(fileName, ".bin");
    
    if ((f = fopen(fileName, "rb")) == NULL) {
        // erro
    } else {
        fread(game->farmer, sizeof(Farmer), 1, f);
        fread(game->shots, sizeof(Shot), 1, f);
        fread(game->milipedes, sizeof(Milipede), 1, f);
        fread(game->spiders, sizeof(Spider), 1, f);
        fread(game->gameState, sizeof(State), 1, f);
        fread(game->menuState, sizeof(MenuState), 1, f);
    }

    fclose(f);

    return;
}

static void SaveGame(char name[], Game game) {
    FILE *f;

    char fileName[STR_LEN];
    strcpy(fileName, name);
    strcat(fileName, ".bin");
    
    if ((f = fopen(fileName, "wb")) == NULL) {
        // erro
    } else {
        fwrite(game.farmer, sizeof(Farmer), 1, f);
        fwrite(game.shots, sizeof(Shot), 1, f);
        fwrite(game.milipedes, sizeof(Milipede), 1, f);
        fwrite(game.spiders, sizeof(Spider), 1, f);
        fwrite(game.gameState, sizeof(State), 1, f);
        fwrite(game.menuState, sizeof(MenuState), 1, f);
    }

    fclose(f);

    return;
}


