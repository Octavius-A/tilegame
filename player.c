#include "player.h"
#include "handleInputs.h"
#include "map.h"
#include "utils.h"

void updatePlayer(Player* player) {
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

	int distX = dirX * player->speed;
	int distY = dirY * player->speed;

	int destX = player->x + distX;
	int destY = player->y + distY;

	bool canMove = false;
	if (destX > 0 and destX < WORLD_WIDTH and destY > 0 and destY < WORLD_HEIGHT) {
		canMove = !gWorldMap[destY][destX].obstructed;
	}

	if (canMove) {
		player->x = destX;
		player->y = destY;
	}
}