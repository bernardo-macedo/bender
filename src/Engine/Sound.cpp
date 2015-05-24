/*
 * Sound.cpp
 *
 *  Created on: 21/05/2015
 *      Author: Pedro2
 */

#include "Sound.h"
#include "Resources.h"

Sound::Sound() {
	sound = NULL;
}

Sound::Sound(std::string file) {
	Open(file);
}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1, sound, times);
}

void Sound::Stop() {
	Mix_HaltChannel(channel);
}

void Sound::Open(std::string file) {
	sound = Resources::GetSound(file);
}

bool Sound::IsOpen() {
	return sound != NULL;
}
