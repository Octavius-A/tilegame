#pragma once

typedef struct {
	int x;
	int y;
	int speed;
} Player;

extern Player gPlayer;

void initPlayer();

void updatePlayer();