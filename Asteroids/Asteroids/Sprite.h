#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include "string"
#include <random>

class CSprite
{
public:
	CSprite(SDL_Renderer* passed_renderer, std::string Path, int start_point_X, int start_point_Y, int change_direction_X, int change_direction_Y, int w, int h, int border[]);
	~CSprite();

	void Draw();

	void SetX(int X);
	void SetY(int Y);

	int GetX();
	int GetY();

	void SetDirection(int new_direction_X, int new_direction_Y);
	int GetDirectionX();
	int GetDirectionY();

	void Motion();

	int GetOrginX();
	int GetOrginY();

private:
	SDL_Texture* image;
	SDL_Rect rect;

	int orgin_X;
	int orgin_Y;

	int start_point_X;
	int start_point_Y;

	int direction_X;
	int direction_Y;

	int left_border_X;
	int right_border_X;
	int top_border_Y;
	int bottom_border_Y;

	double final_counter;

	SDL_Renderer* renderer;
};

