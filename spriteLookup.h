#pragma once

typedef struct {
	int x;
	int y;
} Sprite;

extern Sprite gSpriteLookup[100];
Sprite lookupChar(char c);

void initSpriteLookup();
