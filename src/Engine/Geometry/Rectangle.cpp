/*
 * Rectangle.cpp
 *
 *  Created on: 17/03/2015
 *      Author: Pedro
 */

#include "Rectangle.h"
#include "SDL.h"
#include "../GameRenderer.h"

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

void Rectangle::OnRender(){
	SDL_Renderer* renderer = GameRenderer::GetInstance()->GetRenderer();
	SDL_Rect r;
	r.x = getX();
	r.y = getY();
	r.w = this->w;
	r.h = this->h;
	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
	SDL_RenderFillRect(renderer, &r);
}
