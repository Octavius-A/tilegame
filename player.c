#include "player.h"
#include "handleInputs.h"
#include "map.h"
#include "utils.h"

#include <stdlib.h>

Player gPlayer = {0};

void initPlayer() {
	bool playerPlaced = false;
	int maxTries = 100;
	int numTries = 0;

	// This is broken btw
	int spawnRadius = 25;
	int spawnMinX = (WORLD_WIDTH / 2) - spawnRadius;
	int spawnMaxX = (WORLD_WIDTH / 2) - spawnRadius;
	int spawnMinY = (WORLD_HEIGHT / 2) - spawnRadius;
	int spawnMaxY = (WORLD_HEIGHT / 2) - spawnRadius;

	while (!playerPlaced && numTries < maxTries) {
		numTries++;
		
		int randX = rand() % (spawnMaxX - spawnMinX + 1) + spawnMinX;
		int randY = rand() % (spawnMaxY - spawnMinY + 1) + spawnMinY;
		
		if (!gWorldMap[randY][randX].obstructed) {
			playerPlaced = true;
			gPlayer.x = randX;
			gPlayer.y = randY;
		}
	}

	gPlayer.speed = 1;
}

void updatePlayer() {
	int dirX = 0;
	int dirY = 0;
	
	if (gInputState.h) {
		dirX = -1;
		gInputState.h = false;
	}
	else if (gInputState.j) {
		gInputState.j = false;
		dirY = 1;
	}
	else if (gInputState.k) {
		gInputState.k = false;
		dirY = -1;

	}
	else if (gInputState.l) {
		gInputState.l = false;
		dirX = 1;
	}
	else if (gInputState.y) {
		gInputState.y = false;
		dirX = -1;
		dirY = -1;
	}
	else if (gInputState.u) {
		gInputState.u = false;
		dirX = 1;
		dirY = -1;
	}
	else if (gInputState.b) {
		gInputState.b = false;
		dirX = -1;
		dirY = 1;
	}
	else if (gInputState.n) {
		gInputState.n = false;
		dirX = 1;
		dirY = 1;
	}

	int distX = dirX * gPlayer.speed;
	int distY = dirY * gPlayer.speed;

	int destX = gPlayer.x + distX;
	int destY = gPlayer.y + distY;

	bool canMove = false;
	if (destX > 0 and destX < WORLD_WIDTH and destY > 0 and destY < WORLD_HEIGHT) {
		canMove = !gWorldMap[destY][destX].obstructed;
	}

	if (canMove) {
		gPlayer.x = destX;
		gPlayer.y = destY;
	}
}