#pragma once

#include <SDL.h>
#include "SDL_image.h"
#include <iostream>

class Sprite
{
public:
	Sprite();
	~Sprite();
	void Draw();
private:
	SDL_Texture *image;
	SDL_Rect rect;

};

