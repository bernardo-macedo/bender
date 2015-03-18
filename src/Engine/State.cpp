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
		for(GameObject* go : board){
			if(go->IsPhysicalBody()){
				Physic::GetInstance()->UpdatePhysic((Body*)go);
			}
		}
	}
}

void State::initialize(){
	Setup();
}

void State::Render() {
	OnRender();
	for(GameObject* go : board){
		if(go->IsDead()){
			board.remove(go);
		}
		else{
			go->Update();
			go->Render();
		}
	}
}

void State::Add(GameObject* go){
	board.push_back(go);
}

Drawable* State::GetById(string id) {
	for(GameObject* go : board){
		if(go->getId().compare(id) == 0){
			return go;
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
