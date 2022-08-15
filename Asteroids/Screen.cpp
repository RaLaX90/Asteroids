#include "Screen.h"

// _width - playing field m_screen_width (x)
// _height - m_screen_height of the playing field (y)
Screen::Screen(short _width, short _height, short _map_width, short _map_height):
	m_screen_width(_width), m_screen_height(_height), m_map_width(_map_width), m_map_height(_map_height) {

	m_top_border_Y = (m_screen_height / 2) - (m_map_height / 2);
	m_left_border_X = (m_screen_width / 2) - (m_map_width / 2);
	m_bottom_border_Y = (m_screen_height / 2) + (m_map_height / 2);
	m_right_border_X = (m_screen_width / 2) + (m_map_width / 2);

	win = SDL_CreateWindow("Asteroids_windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screen_width, m_screen_height, SDL_WINDOW_RESIZABLE);
	if (win == nullptr) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error at renderer create", SDL_GetError(), NULL);
		throw "Error at renderer create";
	}
}

Screen::~Screen() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
}

short Screen::GetScreenWidth()
{
	return m_screen_width;
}

short Screen::GetScreenHeight()
{
	return m_screen_height;
}

short Screen::GetMapWidth()
{
	return m_map_width;
}

short Screen::GetMapHeight()
{
	return m_map_height;
}
short Screen::GetTopBorderY()
{
	return m_top_border_Y;
}
short Screen::GetLeftBorderX()
{
	return m_left_border_X;
}
short Screen::GetBottomBorderY()
{
	return m_bottom_border_Y;
}
short Screen::GetRightBorderX()
{
	return m_right_border_X;
}

SDL_Renderer* Screen::GetRenderer()
{
	return renderer;
}