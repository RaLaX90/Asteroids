#pragma once

#include "Sprite.h"

class Bullet : public Sprite
{
public:
	Bullet(SDL_Renderer* _renderer, const char* _path_to_image, COORD _start_point, directionStruct _direction, Uint16 _screen_width, Uint16 _screen_height) : Sprite(_renderer, _path_to_image, _start_point, _direction, _screen_width, _screen_height) {

	}
};