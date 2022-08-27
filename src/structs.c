/*!
 * Source file for object initialization functions
 */

#include "structs.h"
#include "raylib.h"
#include "graphics.h"


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
    farmer->v.x = 0;
    farmer->v.y = 0;

    return;
}