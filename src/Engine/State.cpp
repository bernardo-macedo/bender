/*
 * State.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include "State.h"
#include "Physics/Body.h"
#include "Physics/Physic.h"
#include "Drawable.h"
#include "GameRenderer.h"

using namespace std;

State::State() {
	board = {};
	quitRequested = false;
}

State::~State(){

}

bool State::QuitRequested() {
	return quitRequested;
}

void State::Update() {
	if(SDL_QuitRequested()){
		quitRequested = true;
	}

	ProcessEvents();

	if(!board.empty()){
		for(Drawable* d : board){
			if(d->IsPhysicalBody()){
				Physic::GetInstance()->UpdatePhysic((Body*)d);
			}
		}
	}
}

void State::initialize(){
	Setup();
}

void State::Render() {
	SDL_Rect r;
	r.h = GameRenderer::SCREEN_HEIGHT;
	r.w = GameRenderer::SCREEN_WIDTH;
	r.x = 0;
	r.y = 0;
	SDL_SetRenderDrawColor(GameRenderer::GetInstance()->GetRenderer(), 0, 0, 0, 200);
	SDL_RenderFillRect(GameRenderer::GetInstance()->GetRenderer(), &r);
	for(list<Drawable*>::iterator i = board.begin(); i != board.end(); i++){
		Drawable* d = (Drawable*)*i;
		d->Render();
	}
	OnRender();
}

void State::Add(Drawable* d){
	board.push_back(d);
}

Drawable* State::GetById(string id) {
	for(list<Drawable*>::iterator i = board.begin(); i != board.end(); i++){
		Drawable* d = (Drawable*)*i;
		if(d->getId().compare(id) == 0){
			return d;
		}
	}
	return NULL;
}

void State::ProcessEvents(){
	while (SDL_PollEvent(&event)) {
		switch(event.type){
		case SDL_MOUSEBUTTONDOWN:
			OnMouseDown(event);
			break;
		}
	}
}
