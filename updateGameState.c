#include "updateGameState.h"
#include "map.h"
#include "handleInputs.h"
#include "player.h"

// make some kind of state machine?

GameState currentState = NORMAL;

void updateGameState(Player* player) {
	if (currentState == NORMAL) {
		if (gInputState.esc) {
			gInputState.esc = false;
			currentState = SHOW_PAUSE_SCREEN;
		}
		else {
			updatePlayer(player);
		}
	}
	else if (currentState == SHOW_PAUSE_SCREEN) {
		if (gInputState.esc) {
			gInputState.esc = false;
			currentState = NORMAL;
		}
	}
}