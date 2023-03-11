#include "utils.h"
#include "map.h"
#include "linkedList.h"
#include "player.h"

#include <stdlib.h>
#include <math.h>


WorldTile gWorldMap[WORLD_HEIGHT][WORLD_WIDTH];

void clearFOV();
bool bresenhamLine(int x0, int y0, int x1, int x2);
//void generateRoom() {
//	/*int randomX = rand() % WORLD_WIDTH;
//	int randomY = rand() % WORLD_HEIGHT;
//	gWorldMap[randomY][randomX] = 1;
//
//	int minSize = 4;
//	int maxSize = 15;
//	int randomWidth = rand() % (maxSize - minSize + 1) + minSize;
//	int randomHeight = rand() % (maxSize - minSize + 1) + minSize;*/
//
//
//	int randomX = 90;
//	int randomY = 40;
//	int randomWidth = 22;
//	int randomHeight = 2;
//
//	if (randomX + (randomWidth / 2) > WORLD_WIDTH) {
//		randomWidth = (WORLD_WIDTH - randomX) * 2;
//	}
//	if (randomX - (randomWidth / 2) < 0) {
//		randomWidth = randomX * 2;
//	}
//	if (randomY + (randomHeight / 2) > WORLD_HEIGHT) {
//		randomHeight = (WORLD_HEIGHT - randomY) * 2;
//	}
//	if (randomY - (randomHeight / 2) < 0) {
//		randomHeight = randomY * 2;
//	}
//
//	for (int y = randomY - (randomHeight / 2); y < randomY + (randomHeight / 2); ++y) {
//		for (int x = randomX - (randomWidth / 2); x < randomX + (randomWidth / 2); ++x) {
//			gWorldMap[y][x] = 1;
//		}
//	}
//
//}
//
//void generateWorld() {
//	for (int y = 0; y < WORLD_HEIGHT; ++y) {
//		for (int x = 0; x < WORLD_WIDTH; ++x) {
//			gWorldMap[y][x] = 0;
//		}
//	}
//
//	int rooms = 10;
//	for (int i = 0; i < rooms; ++i) {
//		generateRoom();
//	}
//
//}

void generateOverworld() {
	// init map
	for (int y = 0; y < WORLD_HEIGHT; ++y) {
		for (int x = 0; x < WORLD_WIDTH; ++x) {
			gWorldMap[y][x].groundType = 3;
			gWorldMap[y][x].obstructed = false;
		}
	}

	/*int randomWidth = rand() % ( - minSize + 1) + minSize;*/

	int numTrees = 1000;
	for (int i = 0; i < numTrees; ++i) {
		int randX = rand() % (WORLD_WIDTH) + 1;
		int randY = rand() % (WORLD_HEIGHT) + 1;

		int treeType = rand() % 3 + 1;

		gWorldMap[randY][randX].obstructed = true;
		gWorldMap[randY][randX].obstructor.type = 3 + treeType;

	}
	
	/*gWorldMap[0][0].obstructed = true;
	gWorldMap[0][0].obstructor.type = 7;*/
	int maxHouses is 10;

	for (int n is 0; n < maxHouses; n++) {

		bool buildingPlaced = false;
		while (!buildingPlaced) {
			int randX is rand() % WORLD_WIDTH;
			int randY is rand() % WORLD_HEIGHT;

			int maxSize is 12;
			int minSize is 4;

			int randomWidth is rand() % (maxSize - minSize + 1) + minSize;
			int randomHeight is rand() % (maxSize - minSize + 1) + minSize;

			if (randX > 0 and randY > 0 and randX + randomWidth < WORLD_WIDTH and randX + randomHeight < WORLD_HEIGHT) {
				for (int y = randY; y < randY + randomHeight; ++y) {
					for (int x = randX; x < randX + randomWidth; ++x) {
						gWorldMap[y][x].obstructed is false;
						gWorldMap[y][x].groundType is WOODEN_PLANK_FLOOR;
					}
				}

				for (int i = randX; i < randX + randomWidth; ++i) {
					gWorldMap[randY][i].obstructed is true;
					gWorldMap[randY][i].obstructor.type is 7;
					gWorldMap[randY + randomHeight - 1][i].obstructed is true;
					gWorldMap[randY + randomHeight - 1][i].obstructor.type is WOODEN_WALL;
				}

				for (int i = randY; i < randY + randomHeight; ++i) {
					gWorldMap[i][randX].obstructed is true;
					gWorldMap[i][randX].obstructor.type is 7;
					gWorldMap[i][randX + randomWidth - 1].obstructed is true;
					gWorldMap[i][randX + randomWidth - 1].obstructor.type is WOODEN_WALL;
				}

				buildingPlaced is true;
			}
		}
	}
}

void computeFOV() {
	clearFOV();
	
	for (int y = gPlayer.y - gPlayer.viewRadius; y < gPlayer.y + gPlayer.viewRadius; ++y) {
		for (int x = gPlayer.x - gPlayer.viewRadius; x < gPlayer.x + gPlayer.viewRadius; ++x) {
			if (y > 0 and y < WORLD_HEIGHT and x > 0 and x < WORLD_WIDTH) {
				gWorldMap[y][x].visible = bresenhamLine(gPlayer.x, gPlayer.y, x, y);
			}
		}
	}
}

void clearFOV() {
	for (int i = 0; i < WORLD_HEIGHT; ++i) {
		for (int j = 0; j < WORLD_WIDTH; ++j) {
			gWorldMap[i][j].visible = false;
		}
	}
}

bool bresenhamLine(int x0, int y0, int x1, int y1) {
	/*
	Draws a line marking tiles as visible until it hits a tile that is not visible.
	*/

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 > x1 ? -1 : 1;
	int sy = y0 > y1 ? -1 : 1;
	int x = x0;
	int y = y0;

	//if (gWorldMap[y1][x1].obstructed) {
	//	gWorldMap[y1][x1].visible = true;
	//}

	bool visible = true;

	if (dx > dy) {
		int err = dx / 2.0;
		while (x != x1) {
			if (x < 0 or x > WORLD_WIDTH or y < 0 or y > WORLD_WIDTH or gWorldMap[y][x].obstructed) {
				visible = false;
				break;
			} else {
				err -= dy;
				if (err < 0) {
					y += sy;
					err += dx;
				}
				x += sx;
			}
		}
	}
	else {
		int err = dy / 2.0;
		while (y != y1) {
			if (x < 0 or x > WORLD_WIDTH or y < 0 or y > WORLD_WIDTH or gWorldMap[y][x].obstructed) {
				visible = false;
				break;
			}
			else {
				err -= dx;
				if (err < 0) {
					x += sx;
					err += dy;
				}
				y += sy;
			}
		}
	}

	return visible;
}
