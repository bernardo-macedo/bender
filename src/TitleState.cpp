/*
 * TitleState.cpp
 *
 *  Created on: 20/05/2015
 *      Author: Pedro2
 */

#include "TitleState.h"

#include "Engine/Game.h"
#include "Engine/InputManager.h"
#include "Engine/StageState.h"

TitleState::TitleState() {
	SDL_Color color;
	color.a = 255;
	color.b = 255;
	color.r = 255;
	color.g = 255;
	bg = new Sprite("img/title.jpg", 1, 0);
	title = new Text("font/Call me maybe.ttf", 50, Text::BLENDED, "PRESSIONE ESPACO PARA CONTINUAR...", color, 500, 500);
	title->SetPos(500, 500, true, false);
	timer = new Timer();
	show = true;
	time = 0.6;
	count = 0;
	state = WAITING;
}

void TitleState::Update(float dt) {
	if(InputManager::GetInstance().KeyPress(SPACE_KEY)){
		time = 0.06;
		state = PRESSED;
	}
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}
	if(InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}

	timer->Update(dt);
	if(timer->Get() > time){
		show = !show;
		timer->Restart();
		if(state == PRESSED){
			count ++;
			if(count >= 15){
				count = 0;
				state = WAITING;
				time = 0.6;
				Game::GetInstance()->Push(new StageState());
			}
		}
	}
}

void TitleState::Render() {
	bg->Render(0, 0, 0);
	if(show){
		title->Render(0 ,0);
	}
}

void TitleState::Pause() {
}

void TitleState::Resume() {
}
