/*
 * GameRenderer.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include "GameRenderer.h"

using namespace std;

int GameRenderer::SCREEN_WIDTH = 500;
int GameRenderer::SCREEN_HEIGHT = 500;

GameRenderer::GameRenderer(string title, int width, int height) {
	if(instance == NULL){
		instance = this;
	}
	state = new State();
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

}

GameRenderer::~GameRenderer() {
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void GameRenderer::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);
	TTF_Init();
}

SDL_Renderer* GameRenderer::GetRenderer() {
	return renderer;
}

State* GameRenderer::GetState() {
	return state;
}

GameRenderer* GameRenderer::GetInstance() {
	return instance;
}

void GameRenderer::Run() {
	while(!state->quitRequested()){
		state->Update();
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(17);
	}
}
