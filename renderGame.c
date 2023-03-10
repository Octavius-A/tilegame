#include "renderGame.h"
#include "renderUtils.h"
#include "gameState.h"

// UI entities
#include "pauseMenu.h"
#include "gameMainDisplay.h"

void renderGame() {
	renderClear();
	
	renderGameMainDisplay();
	
	
	// do some shit
	if (gCurrentState == SHOW_PAUSE_MENU) {
		renderPauseMenu();
	}

	renderPresent();
}