#pragma once
#include "player.h"

typedef enum {
	NORMAL,
	SHOW_PAUSE_SCREEN
} GameState;

extern GameState gCurrentState;

void updateGameState(Player* player);