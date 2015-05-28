/*
 * Game.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */
#include <iostream>

#include "SDL_Wrapper.h"
#include "Game.h"
#include "InputManager.h"
#include "Exceptions.h"
#include "Resources.h"


using namespace std;

Game* Game::instance = NULL;
int Game::SCREEN_WIDTH = 1024;
int Game::SCREEN_HEIGHT = 720;

Game::Game(string title, int width, int height) {
	if(instance == NULL){
		instance = this;
	}
	Game::SCREEN_HEIGHT = height;
	Game::SCREEN_WIDTH = width;
	init();
	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if(this->window == NULL){
		throw WINDOW_FAIL;
	}

	this->renderer = SDL_CreateRenderer (window , -1, 0);
	if(this->renderer == NULL){
		throw RENDERER_FAIL;
	}
	physic = new Physic();
	storedState = NULL;

	frameStart = SDL_GetTicks();
}

Game::~Game() {
	while(!stateStack.empty()){
		stateStack.pop();
	}
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	TTF_Init();
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

State* Game::GetCurrentState() {
	return stateStack.top().get();
}

Game* Game::GetInstance() {
	return instance;
}

void Game::Run() {
	if(storedState == NULL){
		throw NO_INITIAL_STATE;
	}
	else{
		stateStack.emplace(storedState);
		storedState = NULL;
	}
	while(!stateStack.empty() && !GetCurrentState()->QuitRequested()){
		CalculaDeltaTime();
		InputManager::GetInstance().Update();
		GetCurrentState()->Update(GetDeltaTime());
		GetCurrentState()->Render();
		SDL_RenderPresent(renderer);

		if(GetCurrentState()->PopRequested()){
			GetCurrentState()->Pause();
			stateStack.pop();
			if(!stateStack.empty()){
				GetCurrentState()->Resume();
			}
		}
		if(storedState != NULL){
			if(!stateStack.empty()){
				GetCurrentState()->Pause();
			}
			stateStack.emplace(storedState);
			GetCurrentState()->Resume();
			storedState = NULL;
		}
		SDL_Delay(15);
	}
	Resources::ClearImages();
	Mix_CloseAudio();
	TTF_Quit();
}

void Game::CalculaDeltaTime() {
	dt = SDL_GetTicks() - frameStart;
	frameStart = SDL_GetTicks();
	dt = dt/1000;
}

float Game::GetDeltaTime() {
	return dt;
}

void Game::Push(State* state){
	storedState = state;
}
