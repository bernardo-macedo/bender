/*
 * Sprite.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include "Sprite.h"
#include "Game.h"

using namespace std;
Sprite::Sprite() {
	texture = NULL;
}

Sprite::Sprite(std::string file) {
	texture = NULL;
	Open(file);
}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {
	texture = Resources::GetImage(file);

	SDL_QueryTexture (texture , NULL, NULL, &width, &height);
	SetClip(0, 0, width, height);
	open = true;
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.h = h;
	clipRect.w = w;
}

void Sprite::Render(int x, int y, int rot) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.h = clipRect.h;
	rect.w = clipRect.w;
	SDL_Point point;
	point.x = clipRect.w/2;
	point.y = clipRect.h/2;

	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture, &clipRect, &rect, rot, &point, SDL_FLIP_NONE);
}

int Sprite::GetWidth() {
	return width;
}

int Sprite::GetHeight() {
	return height;
}

bool Sprite::IsOpen() {
	return open;
}
