#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Map {
public:
	Map();
	

	void LoadMap(int arr[128][160]);
	void DrawMap();
	void Updater();
private:
	SDL_Rect src, dest[200],destslow,destfast,srcslow,srcfast,srcreset,destreset;
	SDL_Texture* sinedot[200];
	SDL_Texture* faster;
	SDL_Texture* slower;
	SDL_Texture* reset;

	int map[128][160];
};