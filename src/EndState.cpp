/*
 * EndState.cpp
 *
 *  Created on: 22/05/2015
 *      Author: Pedro2
 */

#include "EndState.h"
#include "Engine/Game.h"
#include "Engine/StageState.h"
EndState::EndState(StateData *stateData) {
	SDL_Color color;
	color.a = 255;
	color.b = 255;
	color.r = 255;
	color.g = 255;
	if(stateData->playerVictory){
		bg = new Sprite("img/win.jpg", 1, 0);
	}
	else{
		bg = new Sprite("img/lose.jpg", 1, 0);
	}
	instruction = new Text("font/Call me maybe.ttf", 35, Text::SOLID, "Pressione ESC para o MENU, ou ESPACO para jogar novamente",
			color, 500, 500);
	instruction->SetPos(500, 100, true, false);
}

void EndState::Update(float dt) {
	if(InputManager::GetInstance().KeyPress(SPACE_KEY)){
		popRequested = true;
		Game::GetInstance()->Push(new StageState());
	}
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}
}

void EndState::Render() {
	bg->Render(0, 0, 0);
	instruction->Render(0, 0);
}

void EndState::Pause() {
}

void EndState::Resume() {
}
