#include "Sprite.h"

int temporary_X = 0, temporary_Y = 0;

bool is_collision(CSprite* first, CSprite* second) {
	if (((((first->GetX() + first->GetOrginX()) - (second->GetX() + second->GetOrginX())) * ((first->GetX() + first->GetOrginX()) - (second->GetX() + second->GetOrginX())))
		+ (((first->GetY() + first->GetOrginY()) - (second->GetY() + second->GetOrginY())) * ((first->GetY() + first->GetOrginY()) - (second->GetY() + second->GetOrginY())))) < 2 * 30 * 30) {

		return true;
	}
	else {
		return false;
	}
}

void swap_directions(CSprite* first, CSprite* second) {
	temporary_X = first->GetDirectionX();
	temporary_Y = first->GetDirectionY();
	first->SetDirection(second->GetDirectionX(), second->GetDirectionY());
	second->SetDirection(temporary_X, temporary_Y);
}

void destruction(CSprite*& first, CSprite*& second) {
	delete first;
	first = NULL;

	delete second;
	second = NULL;
}

int main(int argc, char* argv[]) {

	//std::string str, s1, s2;
	int SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0, MAP_WIDTH = 0, MAP_HEIGHT = 0, big_asteroids_number = 0, small_asteroids_count = 0;

	//if (argv[1]) {
	//	str = std::string(argv[2]);
	//	auto pos = str.find("x");
	//	s1 = str.substr(0, pos);
	//	s2 = str.substr(pos + 1);
	//	SCREEN_WIDTH = atoi(s1.c_str());
	//	SCREEN_HEIGHT = atoi(s2.c_str());
	//}
	//else {
	SCREEN_WIDTH = 1920; //1550
	SCREEN_HEIGHT = 1080; //800
//}

//if (argv[3]) {
//	str = std::string(argv[4]);
//	auto pos = str.find("x");
//	s1 = str.substr(0, pos);
//	s2 = str.substr(pos + 1);
//	MAP_WIDTH = atoi(s1.c_str());
//	MAP_HEIGHT = atoi(s2.c_str());
//}
//else {
	MAP_WIDTH = 600;
	MAP_HEIGHT = 600;
	//}

	//if (argv[5]) {
	//	big_asteroids_number = atoi(std::string({ argv[6] }).c_str());////////////////////////////////////////////////////////////////
	//}
	//else {
	big_asteroids_number = 5;
	//}

	int top_border_Y = (SCREEN_HEIGHT / 2) - (MAP_HEIGHT / 2);
	int left_border_X = (SCREEN_WIDTH / 2) - (MAP_WIDTH / 2);
	int bottom_border_Y = (SCREEN_HEIGHT / 2) + (MAP_HEIGHT / 2);
	int right_border_X = (SCREEN_WIDTH / 2) + (MAP_WIDTH / 2);

	int border[4] = { top_border_Y, left_border_X, bottom_border_Y, right_border_X };

	bool is_shot_allowed = true;
	int StartTick = 0;

	/*while (argc--)
		std::cout << *argv++ << std::endl;*/

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("big_asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	std::mt19937 gen(std::random_device().operator()());
	std::uniform_int_distribution<int> uid1(left_border_X, right_border_X);
	std::uniform_int_distribution<int> uid2(top_border_Y, bottom_border_Y);

	std::uniform_int_distribution<int> uid3(-5, 5);
	std::uniform_int_distribution<int> uid4(-5, 5);

	//CSprite* big_asteroid = NULL;
	//CSprite* small_asteroid = NULL;
	CSprite* bullet = NULL;

	std::vector<CSprite*> big_asteroids(big_asteroids_number, NULL);
	std::vector<CSprite*> small_asteroids(big_asteroids_number * 2, NULL);
	//CSprite** big_asteroids = new CSprite * [big_asteroids_number];
	//CSprite** small_asteroids = new CSprite * [big_asteroids_number * 2];

	//for (int i = 0; i < big_asteroids_number * 2; i++) {
	//	small_asteroids[i] = NULL;
	//}

	for (int i = 0; i < big_asteroids_number; i++) {
		big_asteroids[i] = new CSprite(renderer, "../data/big_asteroid.png", uid1(gen), uid2(gen), uid3(gen), uid4(gen), 40, 40, border);
	}

	CSprite* background = new CSprite(renderer, "../data/background.png", left_border_X, top_border_Y, 0, 0, MAP_WIDTH, MAP_HEIGHT, border);

	CSprite* spaceship = new CSprite(renderer, "../data/spaceship.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, 30, 30, border);

	SDL_Event e;

	int mouse_x = 0, mouse_y = 0;

	// Exit flag
	bool quit = false;
	bool MoveUp = false;
	bool MoveDown = false;
	bool MoveLeft = false;
	bool MoveRight = false;
	int timeCheck = SDL_GetTicks();
	double speed_up = 0;
	double speed_left = 0;
	double speed_down = 0;
	double speed_right = 0;

	while (!quit) {
		SDL_GetMouseState(&mouse_x, &mouse_y);
		// Event handling
		while (SDL_PollEvent(&e)) {

			//if (e.type == SDL_QUIT) {
			//	quit = true;
			//}

			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: {
					quit = true;
					break;
				}
				case SDLK_w: {
					MoveUp = true;
					break;
				}
				case SDLK_a: {
					MoveLeft = true;
					break;
				}
				case SDLK_s: {
					MoveDown = true;
					break;
				}
				case SDLK_d: {
					MoveRight = true;
					break;
				}
				default: {
					break;
				}
				}
				//quit = true;
			}
			if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.sym) {
				case SDLK_w: {
					MoveUp = false;
					speed_up = 4;
					break;
				}
				case SDLK_a: {
					MoveLeft = false;
					speed_left = 4;
					break;
				}
				case SDLK_s: {
					MoveDown = false;
					speed_down = 4;
					break;
				}
				case SDLK_d: {
					MoveRight = false;
					speed_right = 4;
					break;
				}
				default: {
					break;
				}
				}
			}

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					if (is_shot_allowed) {
						bullet = new CSprite(renderer, "../data/bullet.png", spaceship->GetX() + 10, spaceship->GetY() + 10, mouse_x, mouse_y, 20, 20, border);
					}
				}
			}
		}

		if (spaceship != NULL) {
			if (timeCheck + 10 < (int)SDL_GetTicks()) {

				if (MoveUp) {
					spaceship->SetY(spaceship->GetY() - 4);
					//spaceship->cameraMoving(-4.0f, 0);
				}
				else if (!MoveUp && (speed_up > 0)) {
					spaceship->SetY(spaceship->GetY() - speed_up);
					speed_up -= 0.1;
				}

				if (MoveLeft) {
					spaceship->SetX(spaceship->GetX() - 4);
				}
				else if (!MoveLeft && speed_left > 0) {
					spaceship->SetX(spaceship->GetX() - speed_left);
					speed_left -= 0.1;
				}

				if (MoveDown) {
					spaceship->SetY(spaceship->GetY() + 4);
				}
				else if (!MoveDown && speed_down > 0) {
					spaceship->SetY(spaceship->GetY() + speed_down);
					speed_down -= 0.1;
				}

				if (MoveRight) {
					spaceship->SetX(spaceship->GetX() + 4);
				}
				else if (!MoveRight && speed_right > 0) {
					spaceship->SetX(spaceship->GetX() + speed_right);
					speed_right -= 0.1;
				}

				if ((spaceship->GetX() + spaceship->GetOrginX()) < left_border_X) {
					spaceship->SetX(right_border_X - spaceship->GetOrginX());
				}
				else if ((spaceship->GetX() + spaceship->GetOrginX()) > (right_border_X)) {
					spaceship->SetX(left_border_X - spaceship->GetOrginX());
				}
				else if ((spaceship->GetY() + spaceship->GetOrginY()) < top_border_Y) {
					spaceship->SetY(bottom_border_Y - spaceship->GetOrginY());
				}
				else if (((spaceship->GetY() + spaceship->GetOrginY()) > bottom_border_Y)) {
					spaceship->SetY(top_border_Y - spaceship->GetOrginY());
				}

				timeCheck = (int)SDL_GetTicks();
			}
		}

		// Scene showing
		SDL_RenderClear(renderer);

		background->Draw();

		if (spaceship == NULL) {
			if ((SDL_GetTicks() - StartTick) >= 1000) {
				spaceship = new CSprite(renderer, "../data/spaceship.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, 30, 30, border);
				is_shot_allowed = true;
			}
		}
		else {

			spaceship->Draw();

			if (bullet != NULL) {
				bullet->Motion();
				bullet->Draw();
			}

			for (int i = 0; i < big_asteroids_number * 2; i++) {
				if (i < big_asteroids_number) {
					if (big_asteroids[i] != NULL) {
						big_asteroids[i]->Motion();

						//spaceship vs big
						if (is_collision(spaceship, big_asteroids[i])) {
							destruction(spaceship, big_asteroids[i]);
							StartTick = SDL_GetTicks();
							is_shot_allowed = false;
							break;
						}
						
						//big vs big
						for (int j = i + 1; j < big_asteroids_number - 1; j++) {
							if (big_asteroids[j] != NULL) {
								if (is_collision(big_asteroids[i], big_asteroids[j])) {
									swap_directions(big_asteroids[i], big_asteroids[j]);
								}
							}
						}

						big_asteroids[i]->Draw();

						//bullet vs big
						if (bullet != NULL) {
							if (is_collision(bullet, big_asteroids[i])) {
								small_asteroids[small_asteroids_count] = new CSprite(renderer, "../data/small_asteroid.png", big_asteroids[i]->GetX() + 15, big_asteroids[i]->GetY() + 50, big_asteroids[i]->GetDirectionX() / 2, big_asteroids[i]->GetDirectionY() * 2, 30, 30, border);
								small_asteroids_count++;
								small_asteroids[small_asteroids_count] = new CSprite(renderer, "../data/small_asteroid.png", big_asteroids[i]->GetX() + 50, big_asteroids[i]->GetY() + 15, big_asteroids[i]->GetDirectionX() * 2, big_asteroids[i]->GetDirectionY() / 2, 30, 30, border);
								small_asteroids_count++;

								destruction(bullet, big_asteroids[i]);
								break;
							}
						}
					}
				}

				if (small_asteroids[i] != NULL) {
					small_asteroids[i]->Motion();

					for (int j = 0; j < big_asteroids_number; j++) {
						if (big_asteroids[j] != NULL) {
							if (is_collision(small_asteroids[i], big_asteroids[j])) {
								swap_directions(small_asteroids[i], big_asteroids[j]);
							}
						}
					}

					//for (int j = i + 1; j < (big_asteroids_number * 2) - 1; j++) {
					for (int j = 0; j < big_asteroids_number * 2; j++) {
						if (small_asteroids[j] != NULL && i != j) {
							if (is_collision(small_asteroids[i], small_asteroids[j])) {
								swap_directions(small_asteroids[i], small_asteroids[j]);
							}
						}
					}

					small_asteroids[i]->Draw();

					if (bullet != NULL) {
						if (is_collision(bullet, small_asteroids[i])) {
							destruction(bullet, small_asteroids[i]);
							break;
						}
					}
				}
			}
		}

		//if (bullet != NULL) {
		//	bullet->Motion();
		//	bullet->Draw();

		//	for (int i = 0; i < big_asteroids_number * 2; i++) {
		//		if (i < big_asteroids_number) {
		//			if (big_asteroids[i] != NULL) {
		//				if (is_collision(bullet, big_asteroids[i])) {
		//					small_asteroids[small_asteroids_count] = new CSprite(renderer, "../data/small_asteroid.png", big_asteroids[i]->GetX() + 15, big_asteroids[i]->GetY() + 50, big_asteroids[i]->GetDirectionX() / 2, big_asteroids[i]->GetDirectionY() * 2, 30, 30, border);
		//					small_asteroids_count++;
		//					small_asteroids[small_asteroids_count] = new CSprite(renderer, "../data/small_asteroid.png", big_asteroids[i]->GetX() + 50, big_asteroids[i]->GetY() + 15, big_asteroids[i]->GetDirectionX() * 2, big_asteroids[i]->GetDirectionY() / 2, 30, 30, border);
		//					small_asteroids_count++;

		//					destruction(bullet, big_asteroids[i]);
		//					break;
		//				}
		//			}
		//		}

		//		if (small_asteroids[i] != NULL) {
		//			if (is_collision(bullet, small_asteroids[i])) {
		//				destruction(bullet, small_asteroids[i]);
		//				break;
		//			}
		//		}
		//	}
		//}

		SDL_RenderPresent(renderer);
	}

	delete bullet;

	delete background;
	delete spaceship;

	for (int i = 0; i < big_asteroids_number * 2; i++) {

		if (i < big_asteroids_number) {
			delete big_asteroids[i];
		}

		delete small_asteroids[i];
	}

	big_asteroids.clear();
	small_asteroids.clear();

	//for (auto big_asteroid : big_asteroids)
	//{
	//	delete big_asteroid;
	//}
	//big_asteroids.clear();

	//for (auto small_asteroid : small_asteroids)
	//{
	//	delete small_asteroid;
	//}
	//small_asteroids.clear();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
