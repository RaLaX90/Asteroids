#pragma once

#include "Sprite.h"

class Small_asteroid : public Sprite
{
public:
	Small_asteroid(SDL_Renderer* _renderer, const char* _path_to_image, COORD _start_point, DirectionStruct _direction, uint16_t _screen_width, uint16_t _screen_height) : Sprite(_renderer, _path_to_image, _start_point, _direction, _screen_width, _screen_height) {

	}
};