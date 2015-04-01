/*
 * State.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include <cstdlib>
#include <ctime>

#include "State.h"

State::State() {
	quitRequested = false;
	bg = new Sprite("ocean.jpg");
	srand(time(NULL));
}

State::~State(){
	objectArray.clear();
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::Update() {
	if(SDL_QuitRequested()){
		quitRequested = true;
	}
	Input();
}

void State::Render() {
	bg->Render(0, 0);
	for(int i = objectArray.size() - 1; i >= 0; --i) {
		if(((GameObject*)objectArray[i])->IsDead()){
			objectArray.erase(objectArray.begin() + i);
		}
		else{
			((GameObject*)objectArray[i])->Render();
		}
	}
}

void State::AddObject(float mouseX, float mouseY){
	objectArray.emplace_back(new Face(mouseX, mouseY));
}

void State::Input(){
	SDL_Event event;
	int mouseX, mouseY;
	bool achouFace = false;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				Face* face = (Face*) objectArray[i];

				if(face->GetBox().IsInside((float)mouseX, (float)mouseY)) {
					achouFace = true;
					face->Damage((int)(rand() % 10 + 10));
					break;
				}
			}
			if(!achouFace){
				AddObject(mouseX, mouseY);
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				AddObject((float)mouseX, (float)mouseY);
			}
		}
	}
}
