#pragma once

typedef struct {
	int x;
	int y;
	int speed;
} Player;

void updatePlayer(Player* p);