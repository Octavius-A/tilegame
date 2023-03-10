#include "utils.h"
#include "map.h"
#include "linkedList.h"
#include <stdlib.h>

WorldTile gWorldMap[WORLD_HEIGHT][WORLD_WIDTH];



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

	int numTrees = 100000;
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