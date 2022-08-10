#pragma once

#include "Screen.h"
#include <SDL.h>
#include "SDL_image.h"
#include <windows.h>
#include <iostream>
#include "string"
#include <random>

class Sprite
{
public:
	Sprite(SDL_Renderer* renderer, const char* path_to_image, COORD start_point, COORD direction, short width, short height);
	~Sprite();

	void Draw(SDL_Renderer* renderer);

	//void SetPositionXY(int X, int Y);
	//void SetPositionX(int X);
	//void SetPositionY(int Y);

	int GetPositionX();
	int GetPositionY();

	void SetDirection(COORD new_direction);
	void SetDirectionX(short _X);
	void SetDirectionY(short _Y);
	short GetDirectionX();
	short GetDirectionY();

	void Move(Screen& _scr);

	short GetOrginX();
	short GetOrginY();

private:
	SDL_Texture* image;
	SDL_Rect position;

	COORD orgin;
	//COORD start_point;
	struct {
		double X;
		double Y;
	} direction;

	//double final_counter;
};