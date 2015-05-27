/*
 * Resources.cpp
 *
 *  Created on: 10/04/2015
 *      Author: Pedro
 */

#include "Resources.h"

#include "SDL_Wrapper.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "Exceptions.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;


SDL_Texture* Resources::GetImage(std::string file) {
	std::unordered_map<std::string, SDL_Texture*>::const_iterator got = Resources::imageTable.find(file);
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

Mix_Music* Resources::GetMusic(std::string file) {
	std::unordered_map<std::string, Mix_Music*>::const_iterator got = Resources::musicTable.find(file);
	if(got == Resources::musicTable.end()){
		Mix_Music* music = Mix_LoadMUS(file.c_str());
		if(music  == NULL){
			std::cout << SDL_GetError() << std::endl;
			throw MUSIC_LOAD_FAIL;
		}
		Resources::musicTable.emplace(file, music);
		return music;
	}
	else{
		return got->second;
	}
}

Mix_Chunk* Resources::GetSound(std::string file) {
	std::unordered_map<std::string, Mix_Chunk*>::const_iterator got = Resources::soundTable.find(file);
	if(got == Resources::soundTable.end()){
		Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
		if(chunk  == NULL){
			std::cout << SDL_GetError() << std::endl;
			throw MUSIC_LOAD_FAIL;
		}
		Resources::soundTable.emplace(file, chunk);
		return chunk;
	}
	else{
		return got->second;
	}
}

void Resources::ClearSounds() {
	Resources::soundTable.clear();
}

void Resources::ClearImages() {
	Resources::imageTable.clear();
}

void Resources::ClearMusic() {
	Resources::musicTable.clear();
}

TTF_Font* Resources::GetFont(std::string file, int fontSize) {
	std::ostringstream stream;
	stream << file << fontSize;
	std::string key = stream.str();
	std::unordered_map<std::string, TTF_Font*>::const_iterator got = Resources::fontTable.find(key);
	if(got == Resources::fontTable.end()){
		TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
		if(font == NULL){
			std::cout << SDL_GetError() << std::endl;
			throw FONT_LOAD_FAIL;
		}
		Resources::fontTable.emplace(key, font);
		return font;
	}
	else{
		return got->second;
	}
}

void Resources::ClearFonts() {
	Resources::fontTable.clear();

}
