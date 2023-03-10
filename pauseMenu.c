#include "pauseMenu.h"
#include "renderUtils.h"
#include "linkedList.h"
#include "gameState.h"

typedef enum {
	ROOT = 0,
	CONTROLS_SCREEN = 1,
	ARE_YOU_SURE_QUIT = 2,
	PAUSE_MENU_STATE_COUNT
} PauseMenuState;

PauseMenuState currentState = ROOT;

void updateRootMenu();
void updateControlsScreen();
void updateAreYouSureScreen();
void renderRootMenu();
void renderControlsScreen();
void renderAreYouSureScreen();

typedef enum {
	QUIT		= 0,
	CONTROLS	= 1,
	OPTIONS		= 2,
	MENU_ITEMS_COUNT
} RootMenuItem;

char* rootMenuStrings[MENU_ITEMS_COUNT] = {"QUIT", "CONTROLS", "OPTIONS"};

RootMenuItem currentItem;

typedef enum {
	AYS_NO = 0,
	AYS_YES = 1,
	AYS_COUNT
}AYSMenuItems;

AYSMenuItems currentAYSMenuItem;

void initPauseMenu() {
	currentState = ROOT;
	currentItem = QUIT;
}

void updatePauseMenu() {
	if (currentState == ROOT) {
		updateRootMenu();
	}
	else if (currentState == CONTROLS_SCREEN) {
		updateControlsScreen();
	}
	else if (currentState == ARE_YOU_SURE_QUIT) {
		updateAreYouSureScreen();
	}
}

void updateRootMenu() {
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
	else if (gInputState.rtrn) {
		gInputState.rtrn = false;
		if (currentItem == QUIT) {
			currentAYSMenuItem = AYS_NO;
			currentState = ARE_YOU_SURE_QUIT;
		}
		else if (currentItem == CONTROLS) {
			currentState = CONTROLS_SCREEN;
		}
	}
}

void updateControlsScreen() {
	if (gInputState.esc) {
		gInputState.esc = false;
		currentState = ROOT;
	}
}

void updateAreYouSureScreen() {
	if (gInputState.esc) {
		gInputState.esc = false;
		currentState = ROOT;
	}
	else if (gInputState.downArrow) {
		gInputState.downArrow = false;
		if (currentAYSMenuItem < AYS_COUNT - 1) {
			currentAYSMenuItem++;
		}
		else currentAYSMenuItem = 0;
	}
	else if (gInputState.upArrow) {
		gInputState.upArrow = false;
		if (currentAYSMenuItem > 0) {
			currentAYSMenuItem--;
		}
		else currentAYSMenuItem = AYS_COUNT - 1;
	}
	else if (gInputState.rtrn) {
		gInputState.rtrn = false;
		if (currentAYSMenuItem == AYS_YES) {
			gInputState.quit = true;
		}
		else {
			currentState = ROOT;
		}
	}
}

void renderPauseMenu() {
	if (currentState == ROOT) {
		renderRootMenu();
	}
	else if (currentState == CONTROLS) {
		renderControlsScreen();
	}
	else if (currentState == ARE_YOU_SURE_QUIT) {
		renderAreYouSureScreen();
	}
}

void renderRootMenu() {
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

		renderString(rootMenuStrings[i], menuX + padding + 1, _y, 1);
		_y += padding;
	}
}

void renderControlsScreen() {
	int width = 30;
	int height = 30;
	int x = (SCREEN_WIDTH / 2) - (width / 2);
	int y = (SCREEN_HEIGHT / 2) - (height / 2);

	renderRect(x, y, width, height, 0, 0, 0, 200);
	TitleFrame tf = { x, y, width, height, "CONTROLS INFO" };
	renderTitleFrame(&tf);

	renderString("MOVEMENT (VI KEYS):", x + 1, y + 3, 1);
	renderString("Y K U", x + 4, y + 5, 1);
	renderString(" \\|/", x + 4, y + 6, 1);
	renderString("H-+-L", x + 4, y + 7, 1);
	renderString(" /|\\", x + 4, y + 8, 1);
	renderString("B J N", x + 4, y + 9, 1);

	renderString("ESC = BACK", x + 1, y + height - 2, 1);
}

void renderAreYouSureScreen() {
	int width = 35;
	int height = 10;
	int x = (SCREEN_WIDTH / 2) - (width / 2);
	int y = (SCREEN_HEIGHT / 2) - (height / 2);

	renderRect(x, y, width, height, 0, 0, 0, 200);
	TitleFrame tf = { x, y, width, height, "QUIT" };
	renderTitleFrame(&tf);

	renderString("ARE YOU SURE YOU WANT TO QUIT??", x + 2, y + 2, 1);
	renderString("NO", x + 3, y + 4, 1);
	renderString("YES", x + 3, y + 5, 1);

	renderString(">", x + 2, y + 4 + currentAYSMenuItem, 1);

}