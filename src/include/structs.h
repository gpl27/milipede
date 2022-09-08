/*!
 * Data structure definitions
 */

#ifndef STRUCTS_H
#define STRUCTS_H
#include "raylib.h"

#define NUM_SHROOMS 60
#define SHROOM_SIZE 10

#define NUM_MILIPEDES 1
#define MILIPEDE_SIZE 10
#define MILIPEDE_V 3

#define NUM_SPIDERS 2
#define SPIDER_SIZE 20
#define SPIDER_V 5

#define FARMER_SIZE 20
#define FARMER_V 5

/* State Enumerations */
typedef enum {
    SLAIN,
    PARALYZED,
    ALIVE
} PlayerState;

typedef enum {
    PLANTED,
    HARVESTED,
    EATEN
} ShroomState;

typedef enum {
    DEAD,
    OFFSCENE,
    ONSCENE
} SpiderState;

typedef enum {
    PAUSED,
    PLAYING
} GameState;

typedef enum {
    HIDDEN,
    ACTIVE,
    LOAD,
    SAVE,
    RANKING,
    EXIT_GAME_REQUEST,
    EXIT_GAME
} MenuState;

typedef enum {
    NONE,
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
} Wall;

/* Game Object Structures */
typedef struct {
    Rectangle pos;
    int shrooms;
    PlayerState state;
} Farmer;

typedef struct {
    Rectangle pos;
    ShroomState state;
} Shroom;

// pos will have to be updated when length is incremented and decremented (width and length)
typedef struct {
    Vector2 pos;
    Vector2 v;
    int length;
} Milipede;

typedef struct {
    Rectangle pos;
    Vector2 v;
    SpiderState state;
} Spider;

typedef struct {
    int shots;
    int lives;
    char *name;
    GameState state;
} State;

/* Structure Initialization Functions */
void InitShrooms(Shroom shroom[]);
void InitMilipedes(Milipede milipedes[]);
void InitSpiders(Spider spiders[]);
void InitFarmer(Farmer *farmer);
void InitState(State *gameState);

/* Update Functions */
void UpdateFarmer(Farmer *farmer);
void UpdateState(State *gameState);
void UpdateMenuState(MenuState *menuState);
void UpdateSpiders(Spider spiders[]);

#endif