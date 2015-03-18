/*
 * Sprite.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include "Sprite.h"
#include "GameRenderer.h"

using namespace std;

Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file) {
	if(IsOpen()){
		SDL_DestroyTexture(texture);
	}
	SDL_Renderer* renderer = GameRenderer::GetInstance()->GetRenderer();
	texture = IMG_LoadTexture (renderer, file.c_str());
	if(texture == NULL){
		cout << SDL_GetError() << endl;
		throw IMG_LOAD_FAIL;
	}

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

void Sprite::OnRender() {
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
	SDL_Rect rect;
	rect.x = getX();
	rect.y = getY();
	rect.h = clipRect.h;
	rect.w = clipRect.w;
	SDL_RenderCopyEx( GameRenderer::GetInstance()->GetRenderer(), texture, &clipRect, &rect, getRotation(), NULL, flip);
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

void Sprite::SetCenter(int cX, int cY) {
	center.x = cX;
	center.y = cY;
}
