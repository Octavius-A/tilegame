#include "gameState.h"
#include "map.h"
#include "handleInputs.h"
#include "player.h"
#include "pauseMenu.h"

// make some kind of state machine?

GameState gCurrentState = NORMAL;

void updateGameState() {
	if (gCurrentState == NORMAL) {
		if (gInputState.esc) {
			gInputState.esc = false;
			initPauseMenu();
			gCurrentState = SHOW_PAUSE_MENU;
		}
		else {
			updatePlayer(gPlayer);
		}
	}
	else if (gCurrentState == SHOW_PAUSE_MENU) {
		updatePauseMenu();
	}
}