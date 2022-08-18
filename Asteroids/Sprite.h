#pragma once

#include "Screen.h"
#include <SDL.h>
#include "SDL_image.h"
#include <windows.h>

struct directionStruct {
	short X;
	short Y;
};

class Sprite
{
public:
	Sprite(SDL_Renderer* _renderer, const char* _path_to_image, COORD _start_point, directionStruct _direction, Uint16 _screen_width, Uint16 _screen_height);
	~Sprite();

	void Draw(SDL_Renderer* m_renderer);

	void SetPositionXY(int _X, int _Y);
	void SetPositionX(int _X);
	void SetPositionY(int _Y);

	int GetPositionX();
	int GetPositionY();

	void SetDirectionXY(int _X, int _Y);
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

	directionStruct direction;
};