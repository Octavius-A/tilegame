#include "gameMainDisplay.h"
#include "renderUtils.h"
#include "map.h"
#include "player.h"

int posX = 0;
int posY = 0;
int width = SCREEN_WIDTH;
int height = SCREEN_HEIGHT;
int zoomFactor = 2;

void renderGameMainDisplay() {
	int displayWidth = (width / zoomFactor) - 2;
	int displayHeight = (height / zoomFactor) - 2;

	// for now synch the camera to the player position
	int cameraX = gPlayer.x;
	int cameraY = gPlayer.y;

	int mapViewCenterX = posX + (width / 2);
	int mapViewCenterY = posY + (height / 2);

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

				renderSprite(groundTileSprite, screenX, screenY, zoomFactor);

				if (tile->obstructed) {
					Sprite objectSprite = gSpriteLookup[tile->obstructor.type];
					renderSprite(objectSprite, screenX, screenY, zoomFactor);
				}
			}

		}
	}

	// render the player
	Sprite playerSprite = gSpriteLookup[8];
	renderSprite(playerSprite, mapViewCenterX, mapViewCenterY, zoomFactor);

	TitleFrame mapTitleFrame = { posX, posY, width, height, "ADVENTURE GAME" };
	renderTitleFrame(&mapTitleFrame);
}