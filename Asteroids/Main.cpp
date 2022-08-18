#include "Sprite.h"
#include "Screen.h"
#include "Game.h"

int main(int argc, char* argv[]) {

	try
	{
		Screen m_screen{ 1920, 1080, 1920, 1080 };
		Game game{ &m_screen, 5, 120 };

		//do {
		game.StartGameLoop();

		//} while (game.IsOnceMore());
	}
	catch (const std::exception& Ex)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", Ex.what(), NULL);
	}

	return 0;
}