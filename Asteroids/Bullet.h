#pragma once

#include "Sprite.h"

class Bullet : public Sprite
{
public:
	Bullet(SDL_Renderer* _renderer, const char* _path_to_image, COORD _start_point, DirectionStruct _direction, uint16_t _screen_width, uint16_t _screen_height) : Sprite(_renderer, _path_to_image, _start_point, _direction, _screen_width, _screen_height) {

	}
};