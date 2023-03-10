#pragma once
#include "player.h"

typedef enum {
	NORMAL,
	SHOW_PAUSE_MENU
} GameState;

extern GameState gCurrentState;

void updateGameState();