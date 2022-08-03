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
	Screen(Uint16 _width, Uint16 _height, Uint16 map_width, Uint16 map_height);
	~Screen();
	void SetCursorShow(bool visible);                               // show/hide cursor
	void SetTextAttribute(WORD attr);                               // set text/background color
	void SetCursorPosition(int position_x, int position_y);         // cursor positioning
	void PrintString(int position_x, int position_y, string text);  // character output
	void ClearScreen();												// screen cleaning

	int GetWidth();													// get screen width
	int GetHeight();												// get screen height
	int GetMapWidth();												// get map width
	int GetMapHeight();												// get map height
	int GetTopBorder();												// get screen height
	int GetLeftBorder();											// get screen height
	int GetBottomBorder();											// get screen height
	int GetRightBorder();											// get screen height

private:
	Uint16 width = 0, height = 0, map_width = 0, map_height = 0;		// playing field width and height
	Uint16 top_border = 0, left_border = 0, bottom_border = 0, right_border = 0;		// playing field width and height
	HANDLE m_console_handle = NULL;										// console handle
	CONSOLE_CURSOR_INFO m_old_cursor_info = { 0 }, m_current_cursor_info = { 0 };	// old and new cursor info objects
	WORD m_old_text_attribute = NULL;	

	SDL_Window* win = nullptr;
	SDL_Renderer* renderer = nullptr;// old text attribute
};

