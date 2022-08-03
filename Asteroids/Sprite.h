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
	Sprite(SDL_Renderer* renderer, std::string path_to_image, COORD start_point, COORD direction, Uint16 width, Uint16 height);
	~Sprite();

	void Draw(SDL_Renderer* renderer);

	void SetX(int X);
	void SetY(int Y);

	int GetX();
	int GetY();

	void SetDirection(COORD new_direction);
	int GetDirectionX();
	int GetDirectionY();

	void Move(Screen _scr);

	int GetOrginX();
	int GetOrginY();

private:
	SDL_Texture* image;
	SDL_Rect location;

	COORD orgin;
	COORD start_point;
	COORD direction;

	double final_counter;
};