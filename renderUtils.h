#pragma once
#include "spriteLookup.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define TILE_WIDTH 12
#define TILE_HEIGHT 12
#define SCREEN_WIDTH WINDOW_WIDTH / TILE_WIDTH // Screen width in tiles
#define SCREEN_HEIGHT WINDOW_HEIGHT / TILE_HEIGHT

typedef struct {
	int posX;
	int posY;
	int width;
	int height;
	char* title;
} TitleFrame;


void initRendering();

void quitRendering();

void renderClear();

void renderPresent();

void renderCharacter(char c, int x, int y, int scale);

void renderString(char* string, int x, int y, int scale);

void renderSprite(Sprite sprite, int x, int y, int scale);

void renderRect(int x, int y, int width, int height, int r, int g, int b, int a);

void renderTitleFrame(TitleFrame* frame);