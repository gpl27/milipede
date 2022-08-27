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
#define MILIPEDE_V 5

#define NUM_SPIDERS 2
#define SPIDER_SIZE 20
#define SPIDER_V 10

#define FARMER_SIZE 20

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
    HIDDEN,
    ONSCENE
} SpiderState;

typedef enum {
    START,
    PAUSED,
    PLAYING
} GameState;


/* Game Object Structures */
typedef struct {
    Rectangle pos;
    Vector2 v;
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
#endif