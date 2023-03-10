#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tilePos.h"
#include "spriteLookup.h"
#include "handleInputs.h"
#include "linkedList.h"
#include "map.h"
#include "utils.h"
#include "player.h"
#include "updateGameState.h"
#include "renderUtils.h"
#include "renderGame.h"


typedef struct {
	int posX;
	int posY;
	int width;
	int height;
} MapWindow;

typedef struct {
	int posX;
	int posY;
	int width;
	int height;
	List* stringList;
} LogWindow;

/*TitleFrame mainFrame = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "ADVENTURE"};*/
MapWindow mapWindow = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
LogWindow logWindow = { 1, 70 - 1 , 70, 20 };

Player gPlayer = { WORLD_WIDTH / 2, WORLD_HEIGHT / 2, 1 };

void renderMapWindow(const MapWindow* window);
void renderLogWidow(const LogWindow* window);
void logString(char* string);

int main(int argc, char* args[]) {
	srand(time(NULL));

	initRendering();
	
	logWindow.stringList = newList();
	
	generateOverworld();

	logString("You awake, bleary eyed, in an unfamilliar forest.");
	logString("Golden shafts of sunlight lance through the canopy above");


	
	while (gInputState.quit == false) {

		updateInputState();
		updateGameState(&gPlayer);

		if (gInputState.r) {
			generateOverworld();
			gInputState.r = false;
		}

		renderClear();
		/*renderTitleFrame(&mainFrame);*/
		renderMapWindow(&mapWindow);
		renderLogWidow(&logWindow);
		renderPresent();
	}

	quitRendering();

	return 0;
}

void renderMapWindow(const MapWindow* mapWindow) {
	int zoomFactor = 2;

	int displayWidth = (mapWindow->width / zoomFactor) - 2;
	int displayHeight = (mapWindow->height / zoomFactor) - 2;
	
	// for now synch the camera to the player position
	int cameraX = gPlayer.x;
	int cameraY = gPlayer.y;

	int mapViewCenterX = mapWindow->posX + (mapWindow->width / 2);
	int mapViewCenterY = mapWindow->posY + (mapWindow->height / 2);

	for (int y = cameraY - (displayHeight / 2) - 1; y < cameraY + (displayHeight / 2) + 1; ++y) {
		for (int x = cameraX - (displayWidth / 2) - 1; x < cameraX + (displayWidth / 2) + 1; ++x) {
			if (x < 0 || x > WORLD_WIDTH || y < 0 || y > WORLD_HEIGHT) {
				// do nothing for now (black)
			}
			else {

				WorldTile* tile = &gWorldMap[y][x];
				Sprite groundTileSprite = gSpriteLookup[tile->groundType];
				
				int distX = (cameraX - x) * zoomFactor;
				int distY = (cameraY - y) * zoomFactor;
				int screenX = (mapViewCenterX - distX);
				int screenY = (mapViewCenterY - distY);

				renderSprite(groundTileSprite, screenX, screenY, zoomFactor);

				if (tile->obstructed) {
					Sprite objectSprite = gSpriteLookup[tile->obstructor.type];
					renderSprite(objectSprite, screenX, screenY, zoomFactor);
				}
			}

		}
	}

	// render the player
	Sprite playerSprite = gSpriteLookup[8];
	renderSprite(playerSprite, mapViewCenterX, mapViewCenterY, zoomFactor);

	TitleFrame mapTitleFrame = { mapWindow->posX, mapWindow->posY, mapWindow->width, mapWindow->height, "ADVENTURE GAME" };
	renderTitleFrame(&mapTitleFrame);
}

void renderLogWidow(LogWindow* logWindow) {
	renderRect(logWindow->posX, logWindow->posY, logWindow->width, logWindow->height, 0, 0, 0, 200);
	TitleFrame logWindowFrame = { logWindow->posX, logWindow->posY, logWindow->width, logWindow->height, "LOG" };
	renderTitleFrame(&logWindowFrame);

	
	int drawX = logWindow->posX + 1;
	int drawY = logWindow->posY + logWindow->height - 2;
	ListNode* ln = logWindow->stringList->tail;
	while (ln != NULL and drawY > logWindow->posY) {
		char* string = (char*)ln->data;
		renderString(string, drawX, drawY, 1);
		drawY--;
		ln = ln->prev;
	}
}

void logString(char* string) {
	append(logWindow.stringList, string);
}