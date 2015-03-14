/*
 * Sprite.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include "Sprite.h"
#include "GameRenderer.h"

using namespace std;
Sprite::Sprite() {
	texture = NULL;
}

Sprite::Sprite(std::string file) {
	texture = NULL;
	Open(file);
}

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

void Sprite::Render(int x, int y) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.h = clipRect.h;
	rect.w = clipRect.w;
	SDL_RenderCopy(GameRenderer::GetInstance()->GetRenderer(), texture, &clipRect, &rect);
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
