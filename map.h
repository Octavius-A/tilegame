#pragma once

#include <stdbool.h>

#define WORLD_WIDTH 500
#define WORLD_HEIGHT 500

typedef struct {
	int type;
} GameObject;

typedef struct {
	bool obstructed; // Does it have an obstructing object?
	GameObject obstructor; // a tree, a wall, etc
	int groundType; // id of the ground type 
} WorldTile;

typedef enum TILEID {
	SOLID_STONE = 0,
	COBBLESTONE_GROUND = 1,
	SMILE = 2,
	SHORT_GRASS = 3,
	TREE_1 = 4,
	TREE_2 = 5,
	TREE_3 = 6,
	WOODEN_WALL = 7,
	HUMAN_CLOTH_TUNIC = 8,
	WOODEN_PLANK_FLOOR = 9,
}TILEID;

extern WorldTile gWorldMap[WORLD_HEIGHT][WORLD_WIDTH];

void generateWorld();
void generateOverworld();