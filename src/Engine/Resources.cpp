/*
 * Resources.cpp
 *
 *  Created on: 10/04/2015
 *      Author: Pedro
 */

#include "Resources.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
SDL_Texture* Resources::GetImage(std::string file) {
	std::unordered_map<std::string,SDL_Texture*>::const_iterator got = Resources::imageTable.find(file);
	if(got == Resources::imageTable.end()){
		SDL_Renderer* renderer = Game::GetInstance()->GetRenderer();
			SDL_Texture* texture = IMG_LoadTexture (renderer, file.c_str());
			if(texture == NULL){
				std::cout << SDL_GetError() << std::endl;
				throw IMG_LOAD_FAIL;
			}
			Resources::imageTable.emplace(file, texture);
			return texture;
	}
	else{
		return got->second;
	}

}

void Resources::ClearImages() {
}
