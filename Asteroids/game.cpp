#include "Game.h"

// Constructor
// _scr - an object that outputs to the console
// _latency - delay between position changes in milliseconds
Game::Game(Screen* _scr, Uint8 _latency) :
	m_screen(*_scr)/*, m_latency(_latency)*/ {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}

	m_generator = mt19937(m_rd());
	m_distribution_screen_width = std::uniform_int_distribution<short>(m_screen.GetLeftBorderX(), m_screen.GetRightBorderX());
	m_distribution_screen_height = std::uniform_int_distribution<short>(m_screen.GetTopBorderY(), m_screen.GetBottomBorderY());

	m_distribution_direction_x = uniform_int_distribution<short>(-5, 5);
	m_distribution_direction_y = uniform_int_distribution<short>(-5, 5);

	m_duration = 0;

	for (int i = 0; i < m_big_asteroids_count; i++) {
		big_asteroids[i] = new Sprite(m_screen.GetRenderer(), "../data/big_asteroid.png", COORD{ m_distribution_screen_width(m_generator), m_distribution_screen_height(m_generator) }, COORD{ m_distribution_direction_x(m_generator), m_distribution_direction_y(m_generator) }, 40, 40);
	}

	background = new Sprite(m_screen.GetRenderer(), "../data/background.png", COORD{ m_screen.GetLeftBorderX(), m_screen.GetTopBorderY() }, COORD{ 0, 0 }, m_screen.GetMapWidth(), m_screen.GetMapHeight());

	spaceship = new Sprite(m_screen.GetRenderer(), "../data/spaceship.png", COORD{ static_cast<short>(m_screen.GetScreenWidth() / 2), static_cast<short>(m_screen.GetScreenHeight() / 2) }, COORD{ 0, 0 }, 30, 30);
}

Game::~Game()
{
	delete bullet;

	delete background;
	delete spaceship;

	for (int i = 0; i < m_small_asteroids_count; i++) {

		if (i < m_big_asteroids_count) {
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

void Game::SwapDirections(Sprite* first, Sprite* second)
{
	int temporary_direction_X = first->GetDirectionX();
	int temporary_direction_Y = first->GetDirectionY();
	first->SetDirection(second->GetDirectionX(), second->GetDirectionY());
	second->SetDirection(temporary_direction_X, temporary_direction_Y);
}

void Game::Destruction(Sprite*& first, Sprite*& second)
{
	delete first;
	first = nullptr;

	delete second;
	second = nullptr;
}

bool Game::IsCollision(Sprite* first, Sprite* second)
{
	if (((((first->GetPositionX() + first->GetOrginX()) - (second->GetPositionX() + second->GetOrginX())) * ((first->GetPositionX() + first->GetOrginX()) - (second->GetPositionX() + second->GetOrginX())))
		+ (((first->GetPositionY() + first->GetOrginY()) - (second->GetPositionY() + second->GetOrginY())) * ((first->GetPositionY() + first->GetOrginY()) - (second->GetPositionY() + second->GetOrginY())))) < 2 * 30 * 30) {
		return true;
	}
	else {
		return false;
	}
}

void Game::StartGameLoop() {

	State state = STATE_OK;

	clock_t start_time = clock();
	int mouse_x = 0, mouse_y = 0;
	SDL_Event e;
	bool MoveUp = false;
	bool MoveDown = false;
	bool MoveLeft = false;
	bool MoveRight = false;

	bool is_shot_allowed = true;

	do {
		if (spaceship != nullptr) {
			// Event handling
			while (SDL_PollEvent(&e)) {

				switch (e.type)
				{
				case SDL_KEYDOWN: {
					switch (e.key.keysym.sym) {
					case SDLK_ESCAPE: {
						state = STATE_EXIT;
						break;
					}
					case SDLK_w: {
						MoveUp = true;
						MoveDown = false;
						spaceship->SetDirectionY(spaceship->GetDirectionY() - 2);
						break;
					}
					case SDLK_a: {
						MoveLeft = true;
						MoveRight = false;
						spaceship->SetDirectionX(spaceship->GetDirectionX() - 2);
						break;
					}
					case SDLK_s: {
						MoveDown = true;
						MoveUp = false;
						spaceship->SetDirectionY(spaceship->GetDirectionY() + 2);
						break;
					}
					case SDLK_d: {
						MoveRight = true;
						MoveLeft = false;
						spaceship->SetDirectionX(spaceship->GetDirectionX() + 2);
						break;
					}
					default: {
						break;
					}
					}

					break;
				}
				case SDL_KEYUP: {
					if (e.key.keysym.sym == SDLK_w) {
						MoveUp = false;
					}

					if (e.key.keysym.sym == SDLK_a) {
						MoveLeft = false;
					}

					if (e.key.keysym.sym == SDLK_s) {
						MoveDown = false;
					}

					if (e.key.keysym.sym == SDLK_d) {
						MoveRight = false;
					}

					break;
				}
				case SDL_MOUSEBUTTONDOWN: {
					if (e.button.button == SDL_BUTTON_LEFT) {
						if (is_shot_allowed) {
							SDL_GetMouseState(&mouse_x, &mouse_y);
							bullet = new Sprite(m_screen.GetRenderer(), "../data/bullet.png", COORD{ static_cast<short>(spaceship->GetPositionX() + 10), static_cast<short>(spaceship->GetPositionY() + 10) }, COORD{ static_cast<short>(mouse_x), static_cast<short>(mouse_y) }, 20, 20);
						}
					}

					break;
				}
				default: {
					break;
				}
				}
			}

			if (MoveUp) {
				spaceship->SetDirectionY(spaceship->GetDirectionY() - 1);
			}
			else if (!MoveUp && (spaceship->GetDirectionY() < 0)) {
				spaceship->SetDirectionY(spaceship->GetDirectionY() + 1);
			}

			if (MoveLeft) {
				spaceship->SetDirectionX(spaceship->GetDirectionX() - 1);
			}
			else if (!MoveLeft && (spaceship->GetDirectionX() < 0)) {
				spaceship->SetDirectionX(spaceship->GetDirectionX() + 1);
			}

			if (MoveDown) {
				spaceship->SetDirectionY(spaceship->GetDirectionY() + 1);
			}
			else if (!MoveDown && (spaceship->GetDirectionY() > 0)) {
				spaceship->SetDirectionY(spaceship->GetDirectionY() - 1);
			}

			if (MoveRight) {
				spaceship->SetDirectionX(spaceship->GetDirectionX() + 1);
			}
			else if (!MoveRight && (spaceship->GetDirectionX() > 0)) {
				spaceship->SetDirectionX(spaceship->GetDirectionX() - 1);
			}
		}
		else if (spaceship == nullptr) {
			spaceship = new Sprite(m_screen.GetRenderer(), "../data/spaceship.png", COORD{ static_cast<short>(m_screen.GetScreenWidth() / 2), static_cast<short>(m_screen.GetScreenHeight() / 2) }, COORD{ 0, 0 }, 30, 30);
			is_shot_allowed = true;
		}

		// Clear Scene
		SDL_RenderClear(m_screen.GetRenderer());

		background->Draw(m_screen.GetRenderer());

		for (int i = 0; i < m_small_asteroids_count; i++) {
			if (i < m_big_asteroids_count) {
				if (big_asteroids[i] != nullptr) {
					big_asteroids[i]->Move(m_screen);

					//spaceship vs big
					if (IsCollision(spaceship, big_asteroids[i])) {
						Destruction(spaceship, big_asteroids[i]);
						is_shot_allowed = false;
						break;
					}

					//big vs big
					for (int j = i + 1; j < m_big_asteroids_count - 1; j++) {
						if (big_asteroids[j] != nullptr) {
							if (IsCollision(big_asteroids[i], big_asteroids[j])) {
								SwapDirections(big_asteroids[i], big_asteroids[j]);
							}
						}
					}

					//bullet vs big
					if (bullet != nullptr) {
						if (IsCollision(bullet, big_asteroids[i])) {
							small_asteroids[m_small_asteroids_count] = new Sprite(m_screen.GetRenderer(), "../data/small_asteroid.png", COORD{ static_cast<short>(big_asteroids[i]->GetPositionX() + 15), static_cast<short>(big_asteroids[i]->GetPositionY() + 50) }, COORD{ static_cast<short>(big_asteroids[i]->GetDirectionX() / 2), static_cast<short>(big_asteroids[i]->GetDirectionY() * 2) }, 30, 30);
							m_small_asteroids_count++;
							small_asteroids[m_small_asteroids_count] = new Sprite(m_screen.GetRenderer(), "../data/small_asteroid.png", COORD{ static_cast<short>(big_asteroids[i]->GetPositionX() + 50), static_cast<short>(big_asteroids[i]->GetPositionY() + 15) }, COORD{ static_cast<short>(big_asteroids[i]->GetDirectionX() * 2), static_cast<short>(big_asteroids[i]->GetDirectionY() / 2) }, 30, 30);
							m_small_asteroids_count++;

							Destruction(bullet, big_asteroids[i]);
							break;
						}
					}

					big_asteroids[i]->Draw(m_screen.GetRenderer());
				}
			}

			if (small_asteroids[i] != nullptr) {
				small_asteroids[i]->Move(m_screen);

				//spaceship vs small
				if (IsCollision(spaceship, small_asteroids[i])) {
					Destruction(spaceship, small_asteroids[i]);
					is_shot_allowed = false;
					break;
				}

				//small vs big
				for (int j = 0; j < m_big_asteroids_count; j++) {
					if (big_asteroids[j] != nullptr) {
						if (IsCollision(small_asteroids[i], big_asteroids[j])) {
							SwapDirections(small_asteroids[i], big_asteroids[j]);
						}
					}
				}

				//small vs small
				for (int j = 0; j < m_small_asteroids_count; j++) {
					if (small_asteroids[j] != nullptr && i != j) {
						if (IsCollision(small_asteroids[i], small_asteroids[j])) {
							SwapDirections(small_asteroids[i], small_asteroids[j]);
						}
					}
				}

				//bullet vs small
				if (bullet != nullptr) {
					if (IsCollision(bullet, small_asteroids[i])) {
						Destruction(bullet, small_asteroids[i]);
						break;
					}
				}

				small_asteroids[i]->Draw(m_screen.GetRenderer());
			}
		}

		if (spaceship != nullptr) {
			spaceship->Move(m_screen);
			spaceship->Draw(m_screen.GetRenderer());
		}

		if (bullet != nullptr) {
			bullet->Move(m_screen);
			bullet->Draw(m_screen.GetRenderer());
		}

		SDL_RenderPresent(m_screen.GetRenderer());

		m_duration = clock() - start_time;
	} while (state == STATE_OK);          // play while the snake is alive
}