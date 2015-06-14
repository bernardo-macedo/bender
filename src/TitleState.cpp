/*
 * TitleState.cpp
 *
 *  Created on: May 19, 2015
 *      Author: -Bernardo
 */

#include "TitleState.h"

TitleState::TitleState() {
	//bg.Open("img/title.jpg");
	SDL_Color color;
	color.r = color.g = color.b = 225;
	color.a = 255;
	text = new Text("font/Call me maybe.ttf", 60, Text::SOLID,
			"Press space", color, Game::SCREEN_WIDTH/2 - 150, Game::SCREEN_HEIGHT/2 - 80);
}

TitleState::~TitleState() {
	delete text;
}

void TitleState::Update(float dt) {
	if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		Game::GetInstance()->Push(new Stage());
	}

	this->quitRequested = InputManager::GetInstance().QuitRequested()
				|| InputManager::GetInstance().KeyPress(ESCAPE_KEY);
}

void TitleState::Render() {
	bg.Render(0,0);
	text->Render();
}

void TitleState::Pause() {
}

void TitleState::Resume() {
}
