#pragma once

#include "Screen.h"
#include "Sprite.h"
#include <conio.h>
#include <SDL.h>
#include "SDL_image.h"
#include <windows.h>
#include <random>
#include <mutex>
#include <thread>

using namespace std;

class Game
{
public:
	Game(Screen& _scr, int _latency = 100);
	~Game();
	void StartGameLoop(int mode_number);				// main game loop
	bool IsOnceMore();									// displaying a request and receiving a response from the player
	void WaitForClick(int position_x, int position_y);  // wait for user response
	void PrintLogo();									// print logo
	void EndGame();										// output text at the end of the game
	void swap_directions(Sprite* first, Sprite* second);
	void destruction(Sprite* first, Sprite* second);
	bool IsCollision(Sprite* first, Sprite* second);

private:
	enum Command { CMD_NOCOMMAND = 0, CMD_EXIT, CMD_LEFT, CMD_RIGHT, CMD_UP, CMD_DOWN };
	enum State { STATE_OK = 0, STATE_EXIT, STATE_DIED };
	enum Direction { UP = 0, RIGHT, DOWN, LEFT };

	pair<int, Command> cmd_table[5];					// game command table

	Uint8 latency;										// delay between position changes in milliseconds
	Screen screen;										// screen object
	//Snake snake;										// snake object
	double duration_game;								// duration
	string ver_number = "v 1.0";
	string fieldBorderSymbol = "#";

	Uint8 big_asteroids_number = 0;
	Sprite* bullet = nullptr;
	vector<Sprite*> big_asteroids{ big_asteroids_number, nullptr };
	vector<Sprite*> small_asteroids{ big_asteroids_number * 2, nullptr };
	Sprite* background = nullptr;
	Sprite* spaceship = nullptr;

	random_device m_rd;
	mt19937 m_generator;								// generator for distribution
	uniform_int_distribution<short> m_distribution_screen_width;	// object for random distribution of width
	uniform_int_distribution<short> m_distribution_screen_height;// object for random distribution of height

	uniform_int_distribution<short> m_distribution_direction_x;
	uniform_int_distribution<short> m_distribution_direction_y;

	void drawGameField();					// drawing the playing field
	//COORD createFood();									// position calculation for food
	//void printStatistics();								// output of current statistics
	Command getCommand();								// receiving commands from the keyboard
	void clearkeys();									// clearing the keyboard buffer

	mutex mtx;
	thread t;
};