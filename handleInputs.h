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
} InputState;

extern InputState gInputState;

void updateInputState();