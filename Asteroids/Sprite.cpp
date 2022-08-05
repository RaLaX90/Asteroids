#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* renderer, const char* path_to_image, COORD start_point, COORD direction, short width, short height)
{
	this->orgin.X = width / 2;
	this->orgin.Y = height / 2;

	this->final_counter = 0;

	this->start_point.X = start_point.X;
	this->start_point.Y = start_point.Y;

	this->direction.X = direction.X;
	this->direction.Y = direction.Y;

	this->image = IMG_LoadTexture(renderer, path_to_image);
	if (!image)
	{
		std::cerr << IMG_GetError(); //Can be replaced by SDL_GetError()
	}

	this->location.x = start_point.X;
	this->location.y = start_point.Y;
	this->location.w = width;
	this->location.h = height;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
}

void Sprite::Draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, image, NULL, &location);
}

void Sprite::SetX(int X)
{
	this->location.x = X;
}

void Sprite::SetY(int Y)
{
	this->location.y = Y;
}

int Sprite::GetX()
{
	return this->location.x;
}

int Sprite::GetY()
{
	return this->location.y;
}

void Sprite::SetDirection(COORD new_direction)
{
	this->direction.X = new_direction.X;
	this->direction.Y = new_direction.Y;
}

short Sprite::GetDirectionX()
{
	return this->direction.X;
}

short Sprite::GetDirectionY()
{
	return this->direction.Y;
}

void Sprite::Move(Screen _scr)
{
	if ((this->location.x + this->GetOrginX()) < _scr.GetLeftBorder()) {
		this->location.x = _scr.GetRightBorder() - this->GetOrginX();
	}
	else if ((this->location.x + this->GetOrginX()) > _scr.GetRightBorder()) {
		this->location.x = _scr.GetLeftBorder() - this->GetOrginX();
	}
	else if ((this->location.y + this->GetOrginY()) < _scr.GetTopBorder()) {
		this->location.y = _scr.GetBottomBorder() - this->GetOrginY();
	}
	else if ((this->location.y + this->GetOrginY()) > _scr.GetBottomBorder()) {
		this->location.y = _scr.GetTopBorder() - this->GetOrginY();
	}
	else {
		if (this->location.w == 20) {
			this->location.x = this->start_point.X + (this->direction.X - this->start_point.X) * final_counter;
			this->location.y = this->start_point.Y + (this->direction.Y - this->start_point.Y) * final_counter;
			this->final_counter += 0.02;
		}
		else {
			this->location.x += this->direction.X;
			this->location.y += this->direction.Y;
		}
	}
}

short Sprite::GetOrginX()
{
	return this->orgin.X;
}

short Sprite::GetOrginY()
{
	return this->orgin.Y;
}