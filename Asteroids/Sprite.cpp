#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* _renderer, const char* _path_to_image, COORD _position, directionStruct _direction, Uint16 _screen_width, Uint16 _screen_height)
{
	this->position.x = _position.X;
	this->position.y = _position.Y;
	this->position.w = _screen_width;
	this->position.h = _screen_height;

	this->orgin.X = _screen_width / 2;
	this->orgin.Y = _screen_height / 2;

	this->direction.X = _direction.X;
	this->direction.Y = _direction.Y;

	this->image = IMG_LoadTexture(_renderer, _path_to_image);
	if (!image)
	{
		throw "Error at load image";
	}
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
}

void Sprite::Draw(SDL_Renderer* m_renderer) {
	SDL_RenderCopy(m_renderer, image, NULL, &position);
}

void Sprite::SetPositionXY(int X, int Y)
{
	this->position.x = X;
	this->position.y = Y;
}

void Sprite::SetPositionX(int X)
{
	this->position.x = X;
}

void Sprite::SetPositionY(int Y)
{
	this->position.y = Y;
}

int Sprite::GetPositionX()
{
	return this->position.x;
}

int Sprite::GetPositionY()
{
	return this->position.y;
}

void Sprite::SetDirectionXY(int new_direction_X, int new_direction_Y)
{
	this->direction.X = new_direction_X;
	this->direction.Y = new_direction_Y;
}

void Sprite::SetDirectionX(int _X)
{
	this->direction.X = _X;
}

void Sprite::SetDirectionY(int _Y)
{
	this->direction.Y = _Y;
}

int Sprite::GetDirectionX()
{
	return this->direction.X;
}

int Sprite::GetDirectionY()
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

int Sprite::GetOrginX()
{
	return this->orgin.X;
}

int Sprite::GetOrginY()
{
	return this->orgin.Y;
}