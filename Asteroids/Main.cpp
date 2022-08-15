#include "Sprite.h"
#include "Screen.h"
#include "Game.h"

int main(int argc, char* argv[]) {

	try
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error at renderer create", SDL_GetError(), NULL);

		Screen m_screen{ 1920, 1080, 1920, 1080 };
		Game game{ &m_screen, 120 };

		//do {
			game.StartGameLoop();

		//} while (game.IsOnceMore());
	}
	catch (const std::exception& Ex)
	{
		cerr << "*** " << Ex.what() << endl;
	}

	return 0;
}