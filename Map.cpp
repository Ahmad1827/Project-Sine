#include "Map.h"
#include "game.h"
#include <fstream>
#include "TextureManager.h"
#include <cmath>



const Uint8* keystates = SDL_GetKeyboardState(NULL);
int keypressed[200];
int timepressed[200];
int level = 1,coincount=0;
int constant[200];
int timestart[200];
int screen[128][160];
int ok[200];
int length = 100;
int speed = 4;


Map::Map()
{
	ok[1] = 1;
	for (int i = 1; i <= length; ++i)
	{
		sinedot[i] = TextureManager::LoadTexture("pics\\sinedot.png");
	}
	faster = TextureManager::LoadTexture("pics\\fastersine.png");
	slower = TextureManager::LoadTexture("pics\\slowersine.png");
	reset = TextureManager::LoadTexture("pics\\resetsine.png");

	constant[1] = 200;
	for (int i = 2; i <= length; ++i)
	{
		constant[i] = constant[i - 1] + 20;
	}
	LoadMap(screen);

	for (int i = 1; i <= length; ++i)
	{
		dest[i].w = dest[i].h = 5;
		dest[i].x = -5;
		dest[i].y = 320;
	}
	src.x = src.y = 0;
	src.w = 5;
	src.h = 5;

	srcfast.x = srcslow.x = srcfast.y = srcslow.y = 0;
	srcfast.h = srcslow.h = destslow.h = destfast.h = 20;
	srcfast.w = srcslow.w = destfast.w = destslow.w = 300;

	destfast.x = destslow.x = 30;
	destfast.y = 560;
	destslow.y = 600;
	
	srcreset.x = srcreset.y = 0;
	srcreset.h = 20;
	srcreset.w = 300;

	destreset.x = 400;
	destreset.y = 560;
	destreset.h = 20;
	destreset.w = 300;
}
// sin(0)=0  sin(pi/2) = 1 
void Map::Updater()
{
	if (keystates[SDL_SCANCODE_A])
	{
		speed += 1;
	}
	if (keystates[SDL_SCANCODE_D])
	{
		speed -= 1;
	}if (keystates[SDL_SCANCODE_R])
	{
		for (int i = 1; i <= length; ++i)
		{
			dest[i].x = -5;
			dest[i].y = 320;
			if (i == 1)
			{
				ok[i] = 1;
			}
			else
			{
				ok[i] = 0;
			}
			timestart[i] = 0;
			speed = 2;
		}
	}
	for (int i = 1; i <= length; ++i)
	{
		if (timestart[i] >= 100)
		{
			timestart[i] = 11;
		}

	}
	if (speed < 0)
	{
		int maxi = -10000000;
		int maxindex = -1;
		for (int i = 1; i <= length; ++i)
		{
			if (dest[i].x > maxi)
			{
				maxi = dest[i].x;
				maxindex = i;
			}
		}
		if (maxindex != -1)
		{
			if (dest[maxindex].x < 800)
			{
				for (int i = 1; i <= length; ++i)
				{
					if (dest[i].x < 0)
					{
						dest[i].x = 805;
					}
				}
			}
		}
	}
	else
	{
		int mini = 10000000;
		int minindex = -1;
		for (int i = 1; i <= length; ++i)
		{
			if (dest[i].x < mini)
			{
				mini = dest[i].x;
				minindex = i;
			}
		}
		if (minindex != -1)
		{
			if (dest[minindex].x > 0)
			{
				for (int i = 1; i <= length; ++i)
				{
					if (dest[i].x > 800)
					{
						dest[i].x = -5;
					}
				}
			}
		}
	}
	
	for (int i = 1; i <= length; ++i)
	{
		if (ok[i] == 1)
		{
			timestart[i] += 1;
		}
	}
	for (int i = 1; i <= length; ++i)
	{
		if (timestart[i] >= 10)
		{
			dest[i].x += speed;
			ok[i+1] = 1;
			dest[i].y = sin(double(dest[i].x) / 100.0) * 100 + 300; //+ constant[i];
		}
	}
	
	DrawMap();
}

void Map::LoadMap(int arr[128][160])
{
	for (int row = 0; row < 128; ++row)
	{
		for (int column = 0; column < 160; ++column)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	for (int i = 1; i <= length; ++i)
	{
		TextureManager::Draw(sinedot[i], src, dest[i]);
	}
	TextureManager::Draw(faster, srcfast, destfast);
	TextureManager::Draw(slower, srcslow, destslow);
	TextureManager::Draw(reset, srcreset, destreset);
	/*
	int type = 0;
	for (int row = 0; row < 128; ++row)
	{
		for (int column = 0; column < 160; ++column)
		{
			type = map[row][column];
			dest.x = column * 5;
			dest.y = row * 5;
			//TextureManager::Draw(coinage, src2, dest2);
			if (coincount == 0)
			{
			//	TextureManager::Draw(zero, src3, dest3);
			}
			
			switch (type)
			{
			case 0:
				TextureManager::Draw(sinedot, src, dest);
				break;
			default:
				break;
			}

		}
	}
	*/
}

