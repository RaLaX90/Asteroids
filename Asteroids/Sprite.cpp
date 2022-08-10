#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* renderer, const char* path_to_image, COORD start_point, COORD direction, short width, short height)
{
	this->orgin.X = width / 2;
	this->orgin.Y = height / 2;

	//this->final_counter = 0;

	//this->start_point.X = start_point.X;
	//this->start_point.Y = start_point.Y;

	this->direction.X = direction.X;
	this->direction.Y = direction.Y;

	this->image = IMG_LoadTexture(renderer, path_to_image);
	if (!image)
	{
		std::cerr << IMG_GetError(); //Can be replaced by SDL_GetError()
	}

	this->position.x = start_point.X;
	this->position.y = start_point.Y;
	this->position.w = width;
	this->position.h = height;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
}

void Sprite::Draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, image, NULL, &position);
}

//void Sprite::SetPositionXY(int X, int Y)
//{
//	this->position.x = X;
//	this->position.y = Y;
//}
//
//void Sprite::SetPositionX(int X)
//{
//	this->position.x = X;
//}
//
//void Sprite::SetPositionY(int Y)
//{
//	this->position.y = Y;
//}

int Sprite::GetPositionX()
{
	return this->position.x;
}

int Sprite::GetPositionY()
{
	return this->position.y;
}

void Sprite::SetDirection(COORD new_direction)
{
	this->direction.X = new_direction.X;
	this->direction.Y = new_direction.Y;
}

void Sprite::SetDirectionX(short _X)
{
	this->direction.X = _X;
}

void Sprite::SetDirectionY(short _Y)
{
	this->direction.Y = _Y;
}

short Sprite::GetDirectionX()
{
	return this->direction.X;
}

short Sprite::GetDirectionY()
{
	return this->direction.Y;
}

void Sprite::Move(Screen& _scr)
{
	if ((this->position.x + this->GetOrginX()) < _scr.GetLeftBorderX()) {
		this->position.x = _scr.GetRightBorderX() - this->GetOrginX();
	}
	else if ((this->position.x + this->GetOrginX()) > _scr.GetRightBorderX()) {
		this->position.x = _scr.GetLeftBorderX() - this->GetOrginX();
	}
	else if ((this->position.y + this->GetOrginY()) < _scr.GetTopBorderY()) {
		this->position.y = _scr.GetBottomBorderY() - this->GetOrginY();
	}
	else if ((this->position.y + this->GetOrginY()) > _scr.GetBottomBorderY()) {
		this->position.y = _scr.GetTopBorderY() - this->GetOrginY();
	}
	else {
		this->position.x += this->direction.X;
		this->position.y += this->direction.Y;
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