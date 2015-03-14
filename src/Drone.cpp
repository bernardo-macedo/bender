/*
 * Drone.cpp
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#include "Drone.h"
#include "SDL.h"

Drone::~Drone() {
}

void Drone::OnRender() {
	SDL_Renderer* renderer = GameRenderer::GetInstance()->GetRenderer();
	SDL_Rect r;
	r.w = 60;
	r.h = 20;
	r.x = (int)getX();
	r.y = (int)getY();
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(GameRenderer::GetInstance()->GetRenderer(), &r);
}
