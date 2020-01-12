#include "Sprite.h"


CSprite::CSprite(SDL_Renderer * passed_renderer, std::string Path, int start_point_X, int start_point_Y, int direction_X, int direction_Y, int w, int h, int border[])
{
	this->renderer = passed_renderer;

	this->orgin_X = w / 2;
	this->orgin_Y = h / 2;

	this->final_counter = 0;

	this->start_point_X = start_point_X;
	this->start_point_Y = start_point_Y;

	this->direction_X = direction_X;
	this->direction_Y = direction_Y;

	this->top_border_Y = border[0];
	this->left_border_X = border[1];
	this->bottom_border_Y = border[2];
	this->right_border_X = border[3];

	this->image = IMG_LoadTexture(renderer, Path.c_str());
	if (!image)
	{
		std::cout << IMG_GetError(); // Можно заменить на SDL_GetError()
	}

	rect.x = start_point_X;
	rect.y = start_point_Y;
	rect.w = w;
	rect.h = h;
}


CSprite::~CSprite()
{
	SDL_DestroyTexture(image);
}

void CSprite::Draw() {
	SDL_RenderCopy(renderer, image, NULL, &rect);
}

void CSprite::SetX(int X)
{
	this->rect.x = X;
}

void CSprite::SetY(int Y)
{
	this->rect.y = Y;
}

int CSprite::GetX()
{
	return this->rect.x;
}

int CSprite::GetY()
{
	return this->rect.y;
}

void CSprite::SetDirection(int new_direction_X, int new_direction_Y)
{
	this->direction_X = new_direction_X;
	this->direction_Y = new_direction_Y;
}

int CSprite::GetDirectionX()
{
	return this->direction_X;
}

int CSprite::GetDirectionY()
{
	return this->direction_Y;
}


void CSprite::Motion()
{
	if ((this->rect.x + this->GetOrginX()) < this->left_border_X) {
		this->rect.x = (this->right_border_X) - this->GetOrginX();
	}
	else if ((this->rect.x + this->GetOrginX()) > (this->right_border_X)) {
		this->rect.x = this->left_border_X - this->GetOrginX();
	}
	else if ((this->rect.y + this->GetOrginY()) < this->top_border_Y) {
		this->rect.y = (this->bottom_border_Y) - this->GetOrginY();
	}
	else if ((this->rect.y + this->GetOrginY()) > (this->bottom_border_Y)) {
		this->rect.y = this->top_border_Y - this->GetOrginY();
	}
	else {
		if (this->rect.w == 20) {
			this->rect.x = this->start_point_X + (this->direction_X - this->start_point_X) * final_counter;
			this->rect.y = this->start_point_Y + (this->direction_Y - this->start_point_Y) * final_counter;
			this->final_counter += 0.02;
		}
		else {
			this->rect.x += this->direction_X;
			this->rect.y += this->direction_Y;
		}
	}

}

int CSprite::GetOrginX()
{
	return this->orgin_X;
}

int CSprite::GetOrginY()
{
	return this->orgin_Y;
}



