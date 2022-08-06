#include "Game.h"

// Constructor
// _scr - an object that outputs to the console
// _latency - delay between position changes in milliseconds
Game::Game(Screen& _scr, Uint8 _latency) :
	screen(_scr), latency(_latency) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}

	m_generator = mt19937(m_rd());
	m_distribution_screen_width = uniform_int_distribution<short>(_scr.GetLeftBorder(), _scr.GetRightBorder());
	m_distribution_screen_height = uniform_int_distribution<short>(_scr.GetTopBorder(), _scr.GetBottomBorder());

	m_distribution_direction_x = uniform_int_distribution<short>(-5, 5);
	m_distribution_direction_y = uniform_int_distribution<short>(-5, 5);

	duration_game = 0;

	// initialization of the table of game control commands
	cmd_table[0] = pair<int, Command>(27, CMD_EXIT);   // escape key
	cmd_table[1] = pair<int, Command>('K', CMD_LEFT);  // left arrow
	cmd_table[2] = pair<int, Command>('M', CMD_RIGHT); // right arrow
	cmd_table[3] = pair<int, Command>('H', CMD_UP);    // up arrow
	cmd_table[4] = pair<int, Command>('P', CMD_DOWN);  // arrow to down

	for (int i = 0; i < big_asteroids_number; i++) {
		big_asteroids[i] = new Sprite(screen.GetRenderer(), "../data/big_asteroid.png", COORD{ m_distribution_screen_width(m_generator), m_distribution_screen_height(m_generator) }, COORD{ m_distribution_direction_x(m_generator), m_distribution_direction_y(m_generator) }, 40, 40);
	}

	background = new Sprite(screen.GetRenderer(), "../data/background.png", COORD{ screen.GetLeftBorder(), screen.GetRightBorder() }, COORD{ 0, 0 }, screen.GetMapWidth(), screen.GetMapHeight());

	spaceship = new Sprite(screen.GetRenderer(), "../data/spaceship.png", COORD{ static_cast<short>(screen.GetWidth() / 2), static_cast<short>(screen.GetHeight() / 2) }, COORD{ 0, 0 }, 30, 30);
}

Game::~Game()
{
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
	big_asteroids.shrink_to_fit();

	small_asteroids.clear();
	small_asteroids.shrink_to_fit();

	IMG_Quit();
	SDL_Quit();
}

Game::Command Game::getCommand() {
	int ch;

	ch = _getch();
	if (ch == 0 || ch == 0xe0) {
		ch = _getch();
	}

	for (int i = 0; i < 5; i++) {
		if (cmd_table[i].first == ch) {
			return cmd_table[i].second;
		}
	}

	return Game::Command::CMD_NOCOMMAND;
}

void Game::clearkeys()
{
	while (_kbhit()) {
		_getch();
	}
}

// The food coordinate is calculated randomly.
// Restriction: the coordinate must not fall into the body of the snake.
//COORD Game::createFood() {
//	COORD food{};
//
//	do {
//		food.X = m_distribution_screen_width(m_generator);
//		food.Y = m_distribution_screen_height(m_generator);
//	} while (snake.IsInSnakeBody(food));
//
//	return food;
//}

void Game::drawGameField() {

	screen.ClearScreen();

	for (int i = 0; i < screen.GetHeight(); i++) {
		if (i == 0 || i == screen.GetHeight() - 1) {
			for (int j = 0; j < screen.GetWidth(); j++) {
				screen.PrintString(j, i, fieldBorderSymbol);
			}
		}
		else {
			screen.PrintString(0, i, fieldBorderSymbol);
			screen.PrintString(screen.GetWidth() - 1, i, fieldBorderSymbol);
		}
	}
}

//void Game::printStatistics() {
//	screen.PrintString(0, screen.GetHeight(), "Length: " + to_string(snake.GetSnakeSize()));
//	screen.PrintString(12, screen.GetHeight(), "Game duration: " + to_string(duration_game));
//}

void Game::WaitForClick(short position_x, short position_y) {
	screen.PrintString(screen.GetWidth() / 2, screen.GetHeight() / 2, "Press any key for continue...");
	_getch();
	clearkeys();
}

bool Game::IsOnceMore() {
	screen.PrintString(screen.GetWidth() / 2 - 8, 13, "O n c e    m o r e ? (if not - press 'N' or 'n')");

	int ch = _getch();
	clearkeys();

	if (ch == 'N' || ch == 'n' || ch == 27) {
		return false;
	}

	return true;
}

void Game::PrintLogo() {
	screen.PrintString(screen.GetWidth() / 2 + 7, screen.GetHeight() / 2 - 2, "S  N  A  K  E");
	screen.PrintString(screen.GetWidth() / 2 + 11, screen.GetHeight() / 2 + 10, ver_number);
}

void Game::EndGame() {
	screen.ClearScreen();
	screen.PrintString(0, 0, "Snake " + ver_number);
}

void Game::swap_directions(Sprite* first, Sprite* second)
{
	auto temporary_direction_X = first->GetDirectionX();
	auto temporary_direction_Y = first->GetDirectionY();
	first->SetDirection(COORD{ second->GetDirectionX(), second->GetDirectionY() });
	second->SetDirection(COORD{ temporary_direction_X, temporary_direction_Y });
}

void Game::destruction(Sprite*& first, Sprite*& second)
{
	delete first;
	first = nullptr;

	delete second;
	second = nullptr;
}

bool Game::IsCollision(Sprite* first, Sprite* second)
{
	if (((((first->GetX() + first->GetOrginX()) - (second->GetX() + second->GetOrginX())) * ((first->GetX() + first->GetOrginX()) - (second->GetX() + second->GetOrginX())))
		+ (((first->GetY() + first->GetOrginY()) - (second->GetY() + second->GetOrginY())) * ((first->GetY() + first->GetOrginY()) - (second->GetY() + second->GetOrginY())))) < 2 * 30 * 30) {

		return true;
	}
	else {
		return false;
	}
}

void Game::StartGameLoop(int mode_number) {

	duration_game = 0;

	//thread th(drawGameField);
	drawGameField();           // draw the playing field
	//th.join();

	Command cmd = CMD_NOCOMMAND;
	State state = STATE_OK;
	// delta contains the coordinate increment (dx, dy) for each snake move across the field
	COORD delta{ -1, 0 };                // initial movement - to the left
	//COORD food = createFood();          // calculate food coordinates
	//screen.PrintString(food.X, food.Y, food_symbol);      // display food on the screen

	//printStatistics();                       // display the initial statistics of the game

	clock_t time1, time2, duration;
	time1 = clock();
	int mouse_x = 0, mouse_y = 0;
	SDL_Event e;
	bool MoveUp = false;
	bool MoveDown = false;
	bool MoveLeft = false;
	bool MoveRight = false;

	int timeCheck = SDL_GetTicks();
	double speed_up = 0;
	double speed_left = 0;
	double speed_down = 0;
	double speed_right = 0;

	bool is_shot_allowed = true;
	int StartTick = 0;

	std::string str, s1, s2;
	int /*SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0, MAP_WIDTH = 0, MAP_HEIGHT = 0, */big_asteroids_count = 5, small_asteroids_count = 10;

	do {
		SDL_GetMouseState(&mouse_x, &mouse_y);
		// Event handling
		while (SDL_PollEvent(&e)) {

			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: {
					state = STATE_EXIT;
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
						bullet = new Sprite(screen.GetRenderer(), "../data/bullet.png", COORD{ static_cast<short>(spaceship->GetX() + 10), static_cast<short>(spaceship->GetY() + 10) }, COORD{ static_cast<short>(mouse_x), static_cast<short>(mouse_y) }, 20, 20);
					}
				}
			}
		}

		if (spaceship != nullptr) {
			if (timeCheck + 10 < (int)SDL_GetTicks()) {

				if (MoveUp) {
					spaceship->SetY(spaceship->GetY() - 4);
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

				if ((spaceship->GetX() + spaceship->GetOrginX()) < screen.GetLeftBorder()) {
					spaceship->SetX(screen.GetRightBorder() - spaceship->GetOrginX());
				}
				else if ((spaceship->GetX() + spaceship->GetOrginX()) > screen.GetRightBorder()) {
					spaceship->SetX(screen.GetLeftBorder() - spaceship->GetOrginX());
				}
				else if ((spaceship->GetY() + spaceship->GetOrginY()) < screen.GetTopBorder()) {
					spaceship->SetY(screen.GetBottomBorder() - spaceship->GetOrginY());
				}
				else if (((spaceship->GetY() + spaceship->GetOrginY()) > screen.GetBottomBorder())) {
					spaceship->SetY(screen.GetTopBorder() - spaceship->GetOrginY());
				}

				timeCheck = (int)SDL_GetTicks();
			}
		}

		// Scene showing
		SDL_RenderClear(screen.GetRenderer());

		background->Draw(screen.GetRenderer());

		if (spaceship == nullptr) {
			if ((SDL_GetTicks() - StartTick) >= 1000) {
				spaceship = new Sprite(screen.GetRenderer(), "../data/spaceship.png", COORD{ static_cast<short>(screen.GetWidth() / 2), static_cast<short>(screen.GetHeight() / 2) }, COORD{ 0, 0 }, 30, 30);
				is_shot_allowed = true;
			}
		}
		else {

			spaceship->Draw(screen.GetRenderer());

			if (bullet != nullptr) {
				bullet->Move(screen);
				bullet->Draw(screen.GetRenderer());
			}

			for (int i = 0; i < big_asteroids_count * 2; i++) {
				if (i < big_asteroids_count) {
					if (big_asteroids[i] != nullptr) {
						big_asteroids[i]->Move(screen);

						//spaceship vs big
						if (IsCollision(spaceship, big_asteroids[i])) {
							destruction(spaceship, big_asteroids[i]);
							StartTick = SDL_GetTicks();
							is_shot_allowed = false;
							break;
						}

						//big vs big
						for (int j = i + 1; j < big_asteroids_count - 1; j++) {
							if (big_asteroids[j] != nullptr) {
								if (IsCollision(big_asteroids[i], big_asteroids[j])) {
									swap_directions(big_asteroids[i], big_asteroids[j]);
								}
							}
						}

						big_asteroids[i]->Draw(screen.GetRenderer());

						//bullet vs big
						if (bullet != nullptr) {
							if (IsCollision(bullet, big_asteroids[i])) {
								small_asteroids[small_asteroids_count] = new Sprite(screen.GetRenderer(), "../data/small_asteroid.png", COORD{ static_cast<short>(big_asteroids[i]->GetX() + 15), static_cast<short>(big_asteroids[i]->GetY() + 50) }, COORD{ static_cast<short>(big_asteroids[i]->GetDirectionX() / 2), static_cast<short>(big_asteroids[i]->GetDirectionY() * 2) }, 30, 30);
								small_asteroids_count++;
								small_asteroids[small_asteroids_count] = new Sprite(screen.GetRenderer(), "../data/small_asteroid.png", COORD{ static_cast<short>(big_asteroids[i]->GetX() + 50), static_cast<short>(big_asteroids[i]->GetY() + 15) }, COORD{ static_cast<short>(big_asteroids[i]->GetDirectionX() * 2), static_cast<short>(big_asteroids[i]->GetDirectionY() / 2) }, 30, 30);
								small_asteroids_count++;

								destruction(bullet, big_asteroids[i]);
								break;
							}
						}
					}
				}

				if (small_asteroids[i] != nullptr) {
					small_asteroids[i]->Move(screen);

					for (int j = 0; j < big_asteroids_count; j++) {
						if (big_asteroids[j] != nullptr) {
							if (IsCollision(small_asteroids[i], big_asteroids[j])) {
								swap_directions(small_asteroids[i], big_asteroids[j]);
							}
						}
					}

					for (int j = 0; j < big_asteroids_count * 2; j++) {
						if (small_asteroids[j] != nullptr && i != j) {
							if (IsCollision(small_asteroids[i], small_asteroids[j])) {
								swap_directions(small_asteroids[i], small_asteroids[j]);
							}
						}
					}

					small_asteroids[i]->Draw(screen.GetRenderer());

					if (bullet != nullptr) {
						if (IsCollision(bullet, small_asteroids[i])) {
							destruction(bullet, small_asteroids[i]);
							break;
						}
					}
				}
			}
		}

		SDL_RenderPresent(screen.GetRenderer());

	} while (state == STATE_OK);          // play while the snake is alive

	//screen.PrintString(screen.GetWidth() / 2 - 8, 10, " G a m e    o v e r ");
	//clearkeys();
	//_getch();
	//clearkeys();
}