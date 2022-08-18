#pragma once

#include "Sprite.h"

class Spaceship : public Sprite
{
public:
	Spaceship(SDL_Renderer* _renderer, const char* _path_to_image, COORD _start_point, directionStruct _direction, Uint16 _screen_width, Uint16 _screen_height) : Sprite(_renderer, _path_to_image, _start_point, _direction, _screen_width, _screen_height) {

	}
};