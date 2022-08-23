/*!
 * Source file for graphics related functions
 */

#include "graphics.h"
#include "raylib.h"


void DrawBackground(int gameWidth, int gameHeight, int fontSize) {
    ClearBackground(BLACK);
    DrawRectangle(0, 1.5f*fontSize, gameWidth, gameWidth, DARKGRAY);
}