#include "Screen.h"

// _width - playing field width (x)
// _height - height of the playing field (y)
Screen::Screen(Uint16 _width, Uint16 _height, Uint16 map_width, Uint16 map_height) {

	//if width and height = 0 then set him to default teminal size
	if (_width == 0 && _height == 0) {
		CONSOLE_SCREEN_BUFFER_INFO pcsbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pcsbi);

		width = pcsbi.dwMaximumWindowSize.X;
		height = pcsbi.dwMaximumWindowSize.Y / 2 - 2;
	}
	else {
		width = _width;
		height = _height;
	}

	win = SDL_CreateWindow("Asteroids_windows", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_RESIZABLE);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	}

	top_border = (_height / 2) - (map_height / 2);
	left_border = (_height / 2) - (map_height / 2);
	bottom_border = (_height / 2) + (map_height / 2);
	right_border = (_height / 2) + (map_height / 2);

	m_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_console_handle == INVALID_HANDLE_VALUE) {
		throw "Failed GetStdHandle(): INVALID_HANDLE_VALUE";
	}

	//if (!GetConsoleCursorInfo(m_console_handle, &m_old_cursor_info)) {
	//	throw "Failed GetConsoleCursorInfo()";
	//}

	//m_current_cursor_info.dwSize = m_old_cursor_info.dwSize;
	//m_current_cursor_info.bVisible = m_old_cursor_info.bVisible;

	//CONSOLE_SCREEN_BUFFER_INFO csbi;
	//GetConsoleScreenBufferInfo(m_console_handle, &csbi);
	//m_old_text_attribute = csbi.wAttributes;
}

Screen::~Screen() {
	//SetConsoleCursorInfo(m_console_handle, &m_old_cursor_info);
	//SetConsoleTextAttribute(m_console_handle, m_old_text_attribute);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
}

//void Screen::SetCursorShow(bool visible) {
//	m_current_cursor_info.bVisible = visible;
//	if (!SetConsoleCursorInfo(m_console_handle, &m_current_cursor_info)) {
//		throw "Failed SetConsoleCursorInfo()";
//	}
//}

void Screen::SetTextAttribute(WORD attr) {
	SetConsoleTextAttribute(m_console_handle, attr);
}

void Screen::SetCursorPosition(int position_x, int position_y)
{
	COORD pos = { position_x, position_y };
	SetConsoleCursorPosition(m_console_handle, pos);
}

void Screen::PrintString(int position_x, int position_y, string text)
{
	SetCursorPosition(position_x, position_y);
	cout << text;
}

void Screen::ClearScreen() {
	system("cls");
}

short Screen::GetWidth()
{
	return width;
}

short Screen::GetHeight()
{
	return height;
}

short Screen::GetMapWidth()
{
	return map_width;
}

short Screen::GetMapHeight()
{
	return map_height;
}
short Screen::GetTopBorder()
{
	return top_border;
}
short Screen::GetLeftBorder()
{
	return left_border;
}
short Screen::GetBottomBorder()
{
	return bottom_border;
}
short Screen::GetRightBorder()
{
	return right_border;
}

SDL_Renderer* Screen::GetRenderer()
{
	return renderer;
}
