/*
 * Music.cpp
 *
 *  Created on: 20/05/2015
 *      Author: Pedro2
 */

#include "Music.h"
#include "Resources.h"

#include <stdlib.h>

int Music::ALWAYS = -1;

Music::Music() {
	music = NULL;
}

Music::Music(std::string file) {
	Open(file);
}

void Music::Play(int times) {
	if(Mix_PlayMusic(music, times) < 0){
		std::cout << Mix_GetError() << std::endl;
	}
}

void Music::Stop() {
	Mix_FadeOutMusic(3);
}

void Music::Open(std::string file) {
	music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
	return music != NULL;
}
