#pragma once

#include <cstddef>
#include <SDL.h>
#include "SDL_image.h"
#include <windows.h>
#include <iostream>

using namespace std;

class Screen
{
public:
	Screen(short _width, short _height, short _map_width, short _map_height);
	~Screen();
	//void SetCursorShow(bool visible);                               // show/hide cursor
	void SetTextAttribute(WORD attr);                               // set text/background color
	void SetCursorPosition(short position_x, short position_y);         // cursor positioning
	void PrintString(short position_x, short position_y, string text);  // character output
	void ClearScreen();												// screen cleaning

	short GetWidth();													// get screen width
	short GetHeight();												// get screen height
	short GetMapWidth();												// get map width
	short GetMapHeight();												// get map height
	short GetTopBorderY();												// get screen height
	short GetLeftBorderX();											// get screen height
	short GetBottomBorderY();											// get screen height
	short GetRightBorderX();											// get screen height
	SDL_Renderer* GetRenderer();											// get screen height

private:
	short width = 0, height = 0, map_width = 0, map_height = 0;		// playing field width and height
	short top_border_Y = 0, left_border_X = 0, bottom_border_Y = 0, right_border_X = 0;		// playing field width and height
	HANDLE m_console_handle = NULL;										// console handle
	CONSOLE_CURSOR_INFO m_old_cursor_info = { 0 }, m_current_cursor_info = { 0 };	// old and new cursor info objects
	WORD m_old_text_attribute = NULL;	// old text attribute

	SDL_Window* win = nullptr;
	SDL_Renderer* renderer = nullptr;
};