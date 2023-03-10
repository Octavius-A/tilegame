#include "renderUtils.h"
#include "spriteLookup.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* spriteSheet = NULL;
const char* spriteSheetPath = "assets/tilemap12x12.png";

void loadSpriteSheet();

void initRendering() {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("game window made in C", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if (window) {
		renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

		if (renderer) {
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}

	SDL_ShowCursor(SDL_DISABLE);

	loadSpriteSheet();
}

void quitRendering() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

void renderClear() {
	SDL_RenderClear(renderer);
}

void renderPresent() {
	SDL_RenderPresent(renderer);
}

void loadSpriteSheet(){
	SDL_Surface* tmpSurf = IMG_Load(spriteSheetPath);
	spriteSheet = SDL_CreateTextureFromSurface(renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);
}

void renderCharacter(char c, int x, int y, int scale) {
	Sprite sp = lookupChar(c);
	renderSprite(sp, x, y, scale);
}

void renderString(char* string, int x, int y, int scale) {
	//char* c = string;
	int _x = x;
	int _y = y;
	while (*string != '\0') {
		renderCharacter(*string, _x, _y, scale);
		_x += 1 * scale;
		string++;
	}
}

void renderSprite(Sprite sprite, int x, int y, int scale) {
	SDL_Rect sRect = { sprite.x * TILE_WIDTH, sprite.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
	SDL_Rect dRect = { x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH * scale, TILE_HEIGHT * scale };
	SDL_RenderCopy(renderer, spriteSheet, &sRect, &dRect);
}

void renderRect(int x, int y, int width, int height, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_Rect rect = { x * TILE_WIDTH, y * TILE_WIDTH, width * TILE_WIDTH, height * TILE_HEIGHT };
	SDL_RenderFillRect(renderer, &rect);
}

void renderTitleFrame(TitleFrame* frame) {
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
		renderSprite(vert, frame->posX, ypos, 1);
		renderSprite(vert, frame->posX + frame->width - 1, ypos, 1);
	}

	for (int i = 1 + titleLen; i < frame->width - 1; ++i) {
		int xpos = frame->posX + i;
		renderSprite(horiz, xpos, frame->posY, 1);
	}

	for (int i = 1; i < frame->width - 1; ++i) {
		int xpos = frame->posX + i;
		renderSprite(horiz, xpos, frame->posY + frame->height - 1, 1);
	}

	renderSprite(tlc, frame->posX, frame->posY, 1);
	renderSprite(trc, frame->posX + frame->width - 1, frame->posY, 1);
	renderSprite(blc, frame->posX, frame->posY + frame->height - 1, 1);
	renderSprite(brc, frame->posX + frame->width - 1, frame->posY + frame->height - 1, 1);

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