#pragma once

#include <SDL.h>
#include "SDL_image.h"
#include <windows.h>

class Screen
{
public:
	Screen(short _width, short _height, short _map_width, short _map_height);
	~Screen();

	short GetScreenWidth();													// get m_screen m_screen_width
	short GetScreenHeight();												// get m_screen m_screen_height

	short GetMapWidth();												// get map m_screen_width
	short GetMapHeight();												// get map m_screen_height

	short GetTopBorderY();												// get m_screen m_screen_height
	short GetLeftBorderX();											// get m_screen m_screen_height
	short GetBottomBorderY();											// get m_screen m_screen_height
	short GetRightBorderX();											// get m_screen m_screen_height

	SDL_Renderer* GetRenderer();											// get m_screen m_screen_height

private:
	short m_screen_width = 0, m_screen_height = 0, m_map_width = 0, m_map_height = 0;		// playing field m_screen_width and m_screen_height
	short m_top_border_Y = 0, m_left_border_X = 0, m_bottom_border_Y = 0, m_right_border_X = 0;		// playing field m_screen_width and m_screen_height

	SDL_Window* win = nullptr;
	SDL_Renderer* renderer = nullptr;
};