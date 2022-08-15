#pragma once

typedef struct directionStruct {
	int X;
	int Y;
};

#include "Screen.h"

class Sprite
{
public:
	Sprite(SDL_Renderer* _renderer, const char* _path_to_image, COORD _start_point, directionStruct _direction, int _screen_width, int _screen_height);
	~Sprite();

	void Draw(SDL_Renderer* renderer);

	void SetPositionXY(int X, int Y);
	void SetPositionX(int X);
	void SetPositionY(int Y);

	int GetPositionX();
	int GetPositionY();

	void SetDirection(int new_direction_X, int new_direction_Y);
	void SetDirectionX(int _X);
	void SetDirectionY(int _Y);
	int GetDirectionX();
	int GetDirectionY();

	void Move(Screen& _scr);

	int GetOrginX();
	int GetOrginY();

private:
	SDL_Texture* image;
	SDL_Rect position;

	struct orginStruct {
		int X;
		int Y;
	} orgin;

	struct directionStruct {
		int X;
		int Y;
	} direction;
};