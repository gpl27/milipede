/*
 * Header file for graphics related functions
 */
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "structs.h"

#define FONT_SIZE 20
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT (SCREEN_WIDTH + 3*FONT_SIZE)
#define MENU_HEIGHT (1.5f*FONT_SIZE)
#define MENU_COLOR DARKBLUE
#define FONT_COLOR WHITE

void DrawBackground(void);
void DrawShrooms(Shroom shrooms[]);
void DrawMilipedes(Milipede milipedes[]);
void DrawSpiders(Spider spiders[]);
void DrawFarmer(Farmer farmer);
void DrawStats(State gameState, Farmer farmer);
void DrawExitWindowRequest(void);
void DrawMenu(MenuState menuState);

#endif