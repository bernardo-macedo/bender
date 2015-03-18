/*
 * MyState.cpp
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#include "MyState.h"
#include "Engine/GameRenderer.h"

MyState::MyState() {
	applied = false;
}

MyState::~MyState(){

}

void MyState::Setup(){
	Drone* d = new Drone("teste", 0, 0);
	Drone* d2 = new Drone("teste2", GameRenderer::SCREEN_WIDTH - Drone::WIDTH, 0);
	d->ApplyForce(new Force("gravity", 0, 0.2));
	this->Add(d);
	this->Add(d2);
	d2->ApplyForce(new Force("teste", -0.2, 0.2));
}

void MyState::OnRender(){
	Drone* d = (Drone*)GetById("teste");
	if(d->getY() >= 200 && !applied){
		d->ApplyForce(new Force("antigravity", 0, -0.4));
		applied = true;
	}
}

void MyState::OnMouseDown(SDL_Event event) {
	if(event.button.button == SDL_BUTTON_LEFT){
		if(GameRenderer::FPS == 60)
			GameRenderer::FPS = 30;
		else
			GameRenderer::FPS = 60;
	}
}
