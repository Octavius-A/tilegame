#pragma once
 
#include <SDL.h>
#include <stdbool.h>


typedef struct {
	bool quit;
	bool leftArrow;
	bool rightArrow;
	bool downArrow;
	bool upArrow;
	bool r;
	bool esc;
	bool h, j, k, l, y, u, b, n; // Vim keys
	bool rtrn;
} InputState;

extern InputState gInputState;

void updateInputState();