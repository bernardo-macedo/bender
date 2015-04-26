/*
 * Game.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */
#include <iostream>

#ifdef __linux__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#elif _WIN32

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#else     
#error Platform not supported

#endif

#include "Game.h"
#include "InputManager.h"
#include <iostream>


using namespace std;

Game* Game::instance = NULL;
int Game::SCREEN_WIDTH = 500;
int Game::SCREEN_HEIGHT = 500;

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

	state = new State();
}

Game::~Game() {
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);
	TTF_Init();
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

State* Game::GetState() {
	return state;
}

Game* Game::GetInstance() {
	return instance;
}

void Game::Run() {
	while(!state->QuitRequested()){
		CalculaDeltaTime();
		InputManager::GetInstance().Update();
		state->Update(dt);
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(17);
	}
}

void Game::CalculaDeltaTime() {
	dt = SDL_GetTicks() - frameStart;
	frameStart = SDL_GetTicks();
	dt = dt/1000;
}

float Game::GetDeltaTime() {
	return dt;
}
