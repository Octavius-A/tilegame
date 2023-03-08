#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tilePos.h"
#include "spriteLookup.h"
#include "handleInputs.h"
#include "map.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define TILE_WIDTH 12
#define TILE_HEIGHT 12
const int SCREEN_WIDTH = WINDOW_WIDTH / TILE_WIDTH; // Screen width in tiles
const int SCREEN_HEIGHT = WINDOW_HEIGHT / TILE_HEIGHT;
const char* tilemapPath = "assets/tilemap12x12.png";
SDL_Texture* tilemap = NULL;

int playerX = 10;
int playerY = 10;

typedef struct {
	int posX;
	int posY;
	int width;
	int height;
	char* title;
} TitleFrame;

typedef struct {
	int posX;
	int posY;
	int width;
	int height;
} MapWindow;


typedef struct {
	struct ListItem* prev;
	struct ListItem* next;
	char* item;
} ListItem;

void initSDL();
void quit();

void loadTilemap();
void renderCharacter(char c, int x, int y, int scale);
void renderString(char* string, int startx, int starty);
void renderTile(int x, int y, int sx, int sy, int scale);
void renderTitleFrame(const TitleFrame* window);
void renderMapWindow(const* MapWindow);

int main(int argc, char* args[]) {
	srand(time(NULL));

	initSDL();
	loadTilemap();

	TitleFrame mainFrame = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "ADVENTURE"};
	MapWindow mapWindow = { 1, 1, 100, SCREEN_HEIGHT -2};

	printf("screen width/height %d %d", SCREEN_WIDTH, SCREEN_HEIGHT);
	

	generateOverworld();
	
	while (gInputState.quit == false) {

		updateInputState();

		if (gInputState.upArrow) {
			playerY--;
			gInputState.upArrow = false;
		}
		if (gInputState.downArrow) {
			playerY++;
			gInputState.downArrow = false;
		}
		if (gInputState.rightArrow) {
			playerX++;
			gInputState.rightArrow = false;
		}
		if (gInputState.leftArrow) {
			playerX--;
			gInputState.leftArrow = false;
		}
		if (gInputState.r) {
			generateOverworld();
			gInputState.r = false;
		}

		SDL_RenderClear(gRenderer);
		renderTitleFrame(&mainFrame);
		renderMapWindow(&mapWindow);
		renderString("This is a test... :) /", 20, 20);
		SDL_RenderPresent(gRenderer);
	}

	quit();

	return 0;
}

void initSDL() {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	gWindow = SDL_CreateWindow("game window made in C", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if (gWindow) {
		gRenderer = SDL_CreateRenderer(gWindow, 0, SDL_RENDERER_ACCELERATED);
		
		if (gRenderer) {
			SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		}
	}

	SDL_ShowCursor(SDL_DISABLE);
}

void quit() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	IMG_Quit();
	SDL_Quit();
}

void loadTilemap() {
	SDL_Surface* tmpSurf = IMG_Load(tilemapPath);
	
	tilemap = SDL_CreateTextureFromSurface(gRenderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);
}

void renderString(char* string, int startX, int startY) {
	char* c = string;
	int x = startX;
	int y = startY;

	while (*c != '\0') {
		renderCharacter(*c, x, y, 1);
		x += 1;
		c += 1;
	}
}

void renderCharacter(char c, int x, int y, int scale) {
	Sprite sp = lookupChar(c);
	renderTile(x, y, sp.x, sp.y, scale);
}

void renderTile(int x, int y, int sx, int sy, int scale) {
	SDL_Rect sRect = { sx * TILE_WIDTH, sy * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
	SDL_Rect dRect = { x * (TILE_WIDTH), y * (TILE_HEIGHT), TILE_WIDTH * scale, TILE_HEIGHT * scale };
	SDL_RenderCopy(gRenderer, tilemap, &sRect, &dRect);
}

void renderTitleFrame(const TitleFrame* frame) {
	
	Sprite vert = { 0,1 };
	Sprite horiz = { 1, 1 };
	Sprite tlc = { 2, 1 };
	Sprite trc = { 3, 1 };
	Sprite blc = { 4, 1 };
	Sprite brc = { 5, 1 };

	int titleLen = strlen(frame->title);
	int maxTitleLen = frame->width - 2;
	bool elide = false;
	if (titleLen > maxTitleLen) {
		titleLen = maxTitleLen;
		elide = true;
	}

	for (int i = 1; i < frame->height - 1; ++i) {
		int ypos = frame->posY + i;
		renderTile(frame->posX, ypos, vert.x, vert.y, 1);
		renderTile(frame->posX + frame->width - 1, ypos, vert.x, vert.y, 1);
	}

	for (int i = 1 + titleLen; i < frame->width - 1; ++i) {
		int xpos = frame->posX + i;
		renderTile(xpos, frame->posY, horiz.x, horiz.y, 1);
	}

	for (int i = 1; i < frame->width - 1; ++i) {
		int xpos = frame->posX + i;
		renderTile(xpos, frame->posY + frame->height - 1, horiz.x, horiz.y, 1);
	}

	renderTile(frame->posX, frame->posY, tlc.x, tlc.y, 1);
	renderTile(frame->posX + frame->width - 1, frame->posY, trc.x, trc.y, 1);
	renderTile(frame->posX, frame->posY + frame->height - 1, blc.x, blc.y, 1);
	renderTile(frame->posX + frame->width - 1, frame->posY + frame->height - 1, brc.x, brc.y, 1);

	char* c = frame->title;
	int titleX = frame->posX + 1;
	int titleY = frame->posY;
	int iter = 0;
	while (*c != '\0' && iter < maxTitleLen) {

		if (elide && iter >= maxTitleLen - 3) {
			renderCharacter('.', titleX, titleY, 1);
		}
		else {
			renderCharacter(*c, titleX, titleY, 1);
		}

		c++;
		titleX++;
		iter++;
	}
}

void renderMapWindow(const MapWindow* mapWindow) {
	

	int zoomFactor = 2;

	int displayWidth = (mapWindow->width / zoomFactor) - 2;
	int displayHeight = (mapWindow->height / zoomFactor) - 2;
	
	// for now synch the camera to the player position
	int cameraX = playerX;
	int cameraY = playerY;

	int mapViewCenterX = mapWindow->posX + (mapWindow->width / 2);
	int mapViewCenterY = mapWindow->posY + (mapWindow->height / 2);

	for (int y = cameraY - (displayHeight / 2) - 1; y < cameraY + (displayHeight / 2) + 1; ++y) {
		for (int x = cameraX - (displayWidth / 2) - 1; x < cameraX + (displayWidth / 2) + 1; ++x) {
			if (x < 0 || x > WORLD_WIDTH || y < 0 || y > WORLD_HEIGHT) {
				// do nothing for now (black)
			}
			else {

				WorldTile* tile = &gWorldMap[y][x];
				Sprite groundTileSprite = gSpriteLookup[tile->groundType];
				
				int distX = (cameraX - x) * zoomFactor;
				int distY = (cameraY - y) * zoomFactor;
				int screenX = (mapViewCenterX - distX);
				int screenY = (mapViewCenterY - distY);

				renderTile(screenX, screenY, groundTileSprite.x, groundTileSprite.y, 2);

				if (tile->obstructed) {
					Sprite objectSprite = gSpriteLookup[tile->obstructor.type];
					renderTile(screenX, screenY, objectSprite.x, objectSprite.y, 2);
				}
			}

		}
	}

	// render the player
	Sprite playerSprite = gSpriteLookup[8];
	renderTile(mapViewCenterX, mapViewCenterY, playerSprite.x, playerSprite.y, 2);

	TitleFrame mapTitleFrame = { mapWindow->posX, mapWindow->posY, mapWindow->width, mapWindow->height, "" };
	renderTitleFrame(&mapTitleFrame);
}