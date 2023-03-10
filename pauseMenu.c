#include "pauseMenu.h"
#include "renderUtils.h"
#include "linkedList.h"
#include "gameState.h"

typedef enum {
	QUIT		= 0,
	CONTROLS	= 1,
	OPTIONS		= 2,
	MENU_ITEMS_COUNT
} MenuItems;

char* menuStrings[MENU_ITEMS_COUNT] = {"QUIT", "CONTROLS", "OPTIONS"};

int currentItem;

void initPauseMenu() {
	currentItem = 0;
}

void updatePauseMenu() {
	if (gInputState.esc) {
		gInputState.esc = false;
		gCurrentState = NORMAL; // hmm
	}
	else if (gInputState.downArrow) {
		if (currentItem < MENU_ITEMS_COUNT - 1) {
			currentItem++;
		}
		else {
			currentItem = 0;
		}
		gInputState.downArrow = false;
	}
	else if (gInputState.upArrow) {
		if (currentItem > 0) {
			currentItem--;
		}
		else {
			currentItem = MENU_ITEMS_COUNT - 1;
		}
		gInputState.upArrow = false;
	}
	
}

void renderPauseMenu() {
	int menuWidth = 16;
	int menuHeight = 20;
	int menuX = (SCREEN_WIDTH / 2) - (menuWidth / 2);
	int menuY = (SCREEN_HEIGHT / 2) - (menuHeight / 2);
	
	renderRect(menuX, menuY, menuWidth, menuHeight, 0, 0, 0, 200);

	TitleFrame tf = { menuX, menuY, menuWidth, menuHeight, "MENU" };
	renderTitleFrame(&tf);

	int padding = 2;
	int _y = menuY + padding;
	for (int i = 0; i < MENU_ITEMS_COUNT; ++i) {

		if (i == currentItem) {
			renderCharacter('>', menuX + padding, _y, 1);
		}

		renderString(menuStrings[i], menuX + padding + 1, _y, 1);
		_y += padding;
	}
}