
#include "Framework.h"
#include "Sprite.h"

using namespace std;

/* Test Framework realization */
class MyFramework : public Framework {

public:

	void PreInit(int& width, int& height, bool& fullscreen) override {
		width = 320;
		height = 200;
		fullscreen = false;
	}

	bool Init() {

		return true;
	}

	void Close() {
		quit = true;
	}

	bool Tick() {
		//drawTestBackground();
		return false;
	}

	void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	void onMouseButtonClick(FRMouseButton button, bool isReleased) {

	}

	void onKeyPressed(FRKey k) {
	}

	void onKeyReleased(FRKey k) {
	}

	const char* GetTitle() {
		return "asteroids";
	}
private:
	bool quit;
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (!texture)
	{
		std::cout << IMG_GetError(); // Можно заменить на SDL_GetError()
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

int main(int argc, char *argv[]) {

	//SDL_Window* window = NULL;

	////The surface contained by the window
	//SDL_Surface* screenSurface = NULL;

	////Initialize SDL
	//if (SDL_Init(SDL_INIT_VIDEO) < 0)
	//{
	//	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	//}
	//else
	//{
	//	//Create window
	//	window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//	if (window == NULL)
	//	{
	//		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	//	}
	//	else
	//	{
	//		//Get window surface
	//		screenSurface = SDL_GetWindowSurface(window);

	//		//Fill the surface white
	//		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x0, 0x0, 0xFF));

	//		//Update the surface
	//		SDL_UpdateWindowSurface(window);

	//		//Wait two seconds
	//		SDL_Delay(3000);
	//	}
	//}

	////Destroy window
	//SDL_DestroyWindow(window);

	////Quit SDL subsystems
	//SDL_Quit();

	SDL_DisplayMode displayMode;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	int request = SDL_GetDesktopDisplayMode(0, &displayMode);

	//SDL_Window *win = SDL_CreateWindow("Hello World!", 0, 0, displayMode.w, displayMode.h, SDL_WINDOW_SHOWN);
	SDL_Window *win = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	/*SDL_Rect background_RECT;
		background_RECT.x = 0;
		background_RECT.y = 0;
		background_RECT.w = displayMode.w;
		background_RECT.h = displayMode.h;*/

	SDL_Texture *background = loadTexture("data/background.png", renderer);
	SDL_Texture *spaceship = loadTexture("data/spaceship.png", renderer);


	SDL_Event e;
	// Флаг выхода
	bool quit = false;
	while (!quit) {
		// Обработка событий
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_ESCAPE: {
						quit = true;
						break;
					}
				}
				//quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{	
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					quit = true;
				}
			}
		}
		// Отображение сцены
		SDL_RenderClear(renderer);

		SDL_Rect background_rect;
		background_rect.x = 0;
		background_rect.y = 0;
		background_rect.w = SCREEN_WIDTH;
		background_rect.h = SCREEN_HEIGHT;
		SDL_RenderCopy(renderer, background, NULL, &background_rect);

		SDL_Rect spaceship_rect;
		spaceship_rect.x = SCREEN_WIDTH / 2;
		spaceship_rect.y = SCREEN_HEIGHT / 2;
		spaceship_rect.w = 50;
		spaceship_rect.h = 50;
		SDL_RenderCopy(renderer, spaceship, NULL, &spaceship_rect);

		/*renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		renderTexture(spaceship, renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, 50);*/
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(background);
	SDL_DestroyTexture(spaceship);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	//delete e;
	IMG_Quit();
	SDL_Quit();

	return 0;
}
