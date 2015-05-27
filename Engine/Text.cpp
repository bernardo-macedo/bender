/*
 * Text.cpp
 *
 *  Created on: 21/05/2015
 *      Author: Pedro2
 */

#include "Text.h"
#include "Resources.h"
#include "Game.h"

Text::Text(std::string fontFile, int fontSize, TextStyle style,
		std::string text, SDL_Color color, int x, int y) {
	texture = NULL;
	box.SetX(x);
	box.SetY(y);
	this->color = color;
	this->style = style;
	this->fontSize = fontSize;
	font = Resources::GetFont(fontFile, fontSize);
	this->text = text;
	RemakeTexture();
}

Text::~Text() {
	if(texture != NULL){
		SDL_DestroyTexture(texture);
	}
}

void Text::Render(int cameraX, int cameraY) {
	SDL_Rect rect;
	rect.x = box.GetX() - cameraX;
	rect.y = box.GetY() - cameraY;
	rect.w = box.GetW();
	rect.h = box.GetH();
	SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture, NULL, &rect);
}

void Text::SetPos(int x, int y, bool centerX, bool centerY) {
	int a = x, b = y;
	if(centerX){
		a -= box.GetW()/2;
	}
	if(centerY){
		b -= box.GetH()/2;
	}
	box.SetX(a);
	box.SetY(b);
	RemakeTexture();
}

void Text::SetText(std::string text) {
}

void Text::SetColor(SDL_Color color) {
}

void Text::SetStyle(TextStyle style) {
}

void Text::SetFontSize(int fontSize) {
}

void Text::RemakeTexture() {
	SDL_Surface* surface;
	switch(style){
		case SOLID:
			surface = TTF_RenderText_Solid(font, text.c_str(), color);
			break;
		case SHADED:
			SDL_Color black;
			black.b = 0;
			black.r = 0;
			black.g = 0;
			black.a = 0;
			surface = TTF_RenderText_Shaded(font, text.c_str(), color, black);
			break;
		case BLENDED:
			surface = TTF_RenderText_Blended(font, text.c_str(), color);
			break;
	}
	texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	box.SetW(w);
	box.SetH(h);
}
