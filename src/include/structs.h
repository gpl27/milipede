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
#define FARMER_PTIME 3.0

#define SHOT_V 12
#define SHOT_SIZE 10
#define NUM_SHOTS 100
#define NUM_LIVES 3

/* State Enumerations */
typedef enum {
    SLAIN,
    PARALYZED,
    ALIVE
} FarmerState;

typedef enum {
    PLANTED,
    HARVESTED,
    EATEN
} ShroomState;

typedef enum {
    DEAD,
    STUNNED,
    ONSCENE
} MobState;

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
    OFF,
    ON
} ShotState;

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
    FarmerState state;
    float pTime;
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
    MobState state;
    float pTime;
} Milipede;

typedef struct {
    Rectangle pos;
    Vector2 v;
    MobState state;
} Spider;

typedef struct {
    int shots;
    int lives;
    char *name;
    GameState state;
} State;

typedef struct {
    Rectangle pos;
    ShotState state;
} Shot;

/* Structure Initialization Functions */
void InitShrooms(Shroom shroom[]);
void InitMilipedes(Milipede milipedes[]);
void InitSpiders(Spider spiders[]);
void InitFarmer(Farmer *farmer);
void InitState(State *gameState);
void InitShots(Shot shots[]);

/* Update Functions */
void UpdateFarmer(Farmer *farmer);
void UpdateStates(State *gameState, MenuState *menuState);
void UpdateSpiders(Spider spiders[]);
void UpdateShots(Shot shots[], State *gameState, Farmer farmer);
void CheckCollisions(State *gameState, Farmer *farmer, Shot shots[], Shroom shrooms[], Milipede milipedes[], Spider spiders[]);


#endif