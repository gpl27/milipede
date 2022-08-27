/*!
 * Data structure definitions
 */

#ifndef STRUCTS_H
#define STRUCTS_H
#include "raylib.h"

#define NUM_SHROOMS 60
#define SHROOM_SIZE 10

/* State Enumerations */
typedef enum {
    SLAIN,
    PARALYZED,
    MOVING
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
    Rectangle pos;
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

#endif