/*
 * Resources.h
 *
 *  Created on: 10/04/2015
 *      Author: Pedro
 */

#ifndef ENGINE_RESOURCES_H_
#define ENGINE_RESOURCES_H_

#include "SDL_Wrapper.h"

#include <unordered_map>
#include <string>
#include <memory>

class Resources {
private:
	static std::unordered_map<std::string, TTF_Font*> fontTable;
	static std::unordered_map<std::string, Mix_Chunk*> soundTable;
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
	static std::unordered_map<std::string, Mix_Music*> musicTable;
public:
	static SDL_Texture* GetImage (std::string file);
	static Mix_Music* GetMusic (std::string file);
	static Mix_Chunk* GetSound (std::string file);
	static TTF_Font* GetFont (std::string file, int fontSize);
	static void ClearFonts ();
	static void ClearImages ();
	static void ClearMusic();
	static void ClearSounds();
};

#endif /* ENGINE_RESOURCES_H_ */
