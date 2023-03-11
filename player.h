#pragma once

typedef struct {
	int x;
	int y;
	int speed;
	int viewRadius;
} Player;

extern Player gPlayer;

void initPlayer();

void updatePlayer();