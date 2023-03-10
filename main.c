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
#include "gameState.h"
#include "renderUtils.h"
#include "renderGame.h"

typedef struct {
	int posX;
	int posY;
	int width;
	int height;
	List* stringList;
} LogWindow;

LogWindow logWindow = { 1, 70 - 1 , 70, 20 };


void renderLogWidow(const LogWindow* window);
void logString(char* string);

int main(int argc, char* args[]) {
	srand(time(NULL));

	initRendering();
	
	logWindow.stringList = newList();
	
	generateOverworld();

	initPlayer();

	logString("You awake, bleary eyed, in an unfamilliar forest.");
	logString("Golden shafts of sunlight lance through the canopy above");

	while (gInputState.quit == false) {

		updateInputState();
		updateGameState(&gPlayer);

		if (gInputState.r) {
			generateOverworld();
			gInputState.r = false;
		}

		renderGame();
		/*renderTitleFrame(&mainFrame);*/
		/*renderMapWindow(&mapWindow);*/
		/*renderLogWidow(&logWindow);*/
	}

	quitRendering();

	return 0;
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