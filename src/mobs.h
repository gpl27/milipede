
typedef enum {
    Dead,
    Paralyzed,
    Moving
} PlayerState;

typedef enum {
    Planted,
    Harvested,
    Eaten
} ShroomState;

typedef enum {
    Dead,
    Hidden,
    OnScene
} SpiderState;

typedef enum {
    Start,
    Paused,
    Playing
} GameState;



typedef struct {
    Rectangle pos;
    Vector2 v;
    char *name;
    int shrooms;
    PlayerState state;
} Farmer;


typedef struct {
    Rectangle pos;
    Vector2 v;
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
    GameState state;
} State;