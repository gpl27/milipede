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
static void GetPlayerName(char name[]);
static void LoadGame(char name[], Game *game);
static void SaveGame(char name[], Game game);


/*
 * Initialization functions
 */

// Inicializa cogumelos plantados em posicoes aleatorias
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

// Inicializa milipedes com comprimento de 4 a 10 em posicao aleatoria
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

// Inicializa aranhas em posicoes aleatorias com velocidade aleatoria baseada na velocidade fixa na constante
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

// Inicializa fazendeiro vivo no centro da tela de jogo com 0 cogumelos colhidos
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

// Inicializa o estado do jogo como jogando e com o numero de vidas e tiros definidos por constantes
void InitState(State *gameState) {
    gameState->lives = NUM_LIVES;
    gameState->shots = NUM_SHOTS;
    gameState->state = PLAYING;
    strcpy(gameState->name, "\0");
    return;
}

// Inicializa todos os tiros como desativados
void InitShots(Shot shots[]) {
    int i;

    for (i=0; i<NUM_SHOTS; i++) {
        shots[i].state = OFF;
        shots[i].pos.width = SHOT_SIZE;
        shots[i].pos.height = SHOT_SIZE;
    }

    return;
}

// Inicializa o jogo com as variaveis que contem os dados do jogo
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

// Atualiza fazendeiro
void UpdateFarmer(Farmer *farmer) {
    
    // Logica de movimento de acordo com as setas do teclado
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

    // Mantem o fazendeiro paralizado ate que alguns ciclos de jogo passem
    if (farmer->state == PARALYZED) {
        farmer->pTime += GetFrameTime();
        farmer->state = (farmer->pTime > FARMER_PTIME)? ALIVE : PARALYZED;
    }


    return;
}

// Atualiza os estados do jogo
void UpdateStates(Game *game) {
    // Instanciacao das variaveis do jogo
    MenuState *menuState = game->menuState;
    State *gameState = game->gameState;

    // Atualiza o menu de acordo com o seu estado atual
    // e o atualiza caso alguma tecla seja apertada
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
            if (IsKeyPressed(KEY_ENTER)) {
                LoadGame(gameState->name, game);
                *menuState = ACTIVE;
            }
            GetPlayerName(gameState->name);
            break;
        case SAVE:
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

// Atualiza aranhas
void UpdateSpiders(Spider spiders[]) {
    int i;

    for (i = 0; i < NUM_SPIDERS; i++) {
        // Se a aranha nao esta morta
        if (spiders[i].state != DEAD) {
            // Testa as possiveis colisoes da aranha com os extremos do cenario
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

            // Move a atual aranha
            spiders[i].pos.x += spiders[i].v.x;
            spiders[i].pos.y += spiders[i].v.y;
        } 

        // Se a atual aranha esta morta
        if (spiders[i].state == DEAD) {
            // Garante que a aranha se mantenha paralizada por alguns ciclos de jogo
            spiders[i].pTime += GetFrameTime();

            // Se o tempo de paralizacao ja foi excedido
            if (spiders[i].pTime > DEATH_TIME) {
                // Cria uma nova aranha e a coloca em alguma posicao aleatoria no cenario
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

// Atualiza milipedes
void UpdateMilipedes(Milipede milipedes[]) {

    int i;
    for (i = 0; i < NUM_MILIPEDES; i++) {
        // Se a atual milipede esta morta
        if (milipedes[i].state == DEAD) {
            // Garante que ela fique paralizada por alguns ciclos de jogo
            milipedes[i].pTime += GetFrameTime();

            // Se o tempo de paralizacao foi excedido
            if (milipedes[i].pTime > DEATH_TIME) {
                // Gera uma nova milipede no cenario em alguma posicao aleatoria
                milipedes[i].length = GetRandomValue(4, 10);
                milipedes[i].pos.x = GetRandomValue(0, (SCREEN_WIDTH - SHROOM_SIZE));
                milipedes[i].pos.y = GetRandomValue(MENU_HEIGHT, (SCREEN_WIDTH/4*3));
                milipedes[i].pTime = 0.0f;
                milipedes[i].state = ONSCENE;
            }
            
        }

        // Se a milipede esta desorientada (porque foi atingida)
        if (milipedes[i].state == STUNNED) {
            // Mantem ela paralizada por alguns ciclos de jogo
            milipedes[i].pTime += GetFrameTime();
            milipedes[i].state = (milipedes[i].pTime > STUN_TIME)? ONSCENE : STUNNED;
        }

        // Se a milipe esta no cenario
        if (milipedes[i].state == ONSCENE) {
            // Testa se ela colidiu com algum extremo horizontal e a reposiciona no cenario caso isso tenha acontecido
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

// Atualiza os tiros
void UpdateShots(Shot shots[], State *gameState, Farmer farmer) {
    int i;
    // O indice do ultimo tiro eh a diferenca entre o numero inicial de tiros com o numero de tiros dados
    int lastShot = (NUM_SHOTS - gameState->shots) - 1;

    // Checa se o tiro foi dado
    if (IsKeyPressed(KEY_SPACE)) {
        if (gameState->shots > 0 && farmer.state != PARALYZED) {
            // POssivel bugzin aqui kkk
            shots[++lastShot].pos.x = farmer.pos.x;
            shots[lastShot].pos.y = farmer.pos.y;
            shots[lastShot].state = ON;
            gameState->shots--;
        }
    }

    // Movimento do tiro
    // Obs: O numero 10 foi utilizado para movimentar os ultimos 10 tiros disparados
    for(i = lastShot; ((i > lastShot - 10) && (i >= 0)); i--) {
        if (shots[i].state == ON) {
            shots[i].pos.y -= SHOT_V;
            if (CheckCollisionBoundary(shots[i].pos)) {
                shots[i].state = OFF;
            }
        }
    }
}

// Checa colisoes
void CheckCollisions(Game *game) {
    // Instanciacao das variaveis do jogo
    Farmer *farmer = game->farmer;
    Shot *shots = game->shots;
    Shroom *shrooms = game->shrooms;
    Milipede *milipedes = game->milipedes;
    Spider *spiders = game->spiders;
    State *gameState = game->gameState; 

    // O indice do ultimo tiro eh a diferenca entre o numero inicial de tiros com o numero de tiros dados
    int lastShot = (NUM_SHOTS - gameState->shots) - 1;
    int i;
    int j;
    // Obs: O numero 10 foi utilizado para testar a colisao dos ultimos 10 tiros disparados
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

static void GetPlayerName(char name[]) {
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


