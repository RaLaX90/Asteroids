#pragma once

#include "Screen.h"
#include "Sprite.h"
//#include "Big_asteroid.h"
//#include "Small_asteroid.h"
//#include "Spaceship.h"
//#include "Bullet.h"
//#include "Background.h"
#include <SDL.h>
#include "SDL_image.h"
#include <random>
#include <mutex>
#include <thread>

using namespace std;

class Game
{
public:
	Game(Screen* _scr, Uint8 _big_asteroids_count, Uint8 _latency = 100);
	~Game();
	void StartGameLoop();				// main game loop
	void SwapDirections(Sprite* _first, Sprite* _second);
	void Destruction(Sprite*& _first, Sprite*& _second);
	bool IsCollision(Sprite* _first, Sprite* _second);

private:
	enum State { STATE_OK = 0, STATE_EXIT, STATE_DIED };

	//Uint8 m_latency;										// delay between position changes in milliseconds
	Screen m_screen;										// m_screen object
	clock_t m_duration;									// game m_duration

	Uint8 m_big_asteroids_count = 0, m_small_asteroids_count = 0;
	Sprite* spaceship = nullptr;
	Sprite* background = nullptr;
	Sprite* bullet = nullptr;
	vector<Sprite*> big_asteroids{ m_big_asteroids_count, nullptr };
	vector<Sprite*> small_asteroids{ m_big_asteroids_count * 2, nullptr };

	random_device m_rd;
	mt19937 m_generator;											// generator for distribution
	uniform_int_distribution<short> m_distribution_screen_width;	// object for random distribution of m_screen_width
	uniform_int_distribution<short> m_distribution_screen_height;	// object for random distribution of m_screen_height

	uniform_int_distribution<short> m_distribution_direction_x;
	uniform_int_distribution<short> m_distribution_direction_y;

	mutex m_mtx;
	thread m_thread;
};