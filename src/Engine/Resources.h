/*
 * Resources.h
 *
 *  Created on: 10/04/2015
 *      Author: Pedro
 */

#ifndef ENGINE_RESOURCES_H_
#define ENGINE_RESOURCES_H_

#include <SDL_render.h>
#include <unordered_map>
#include <string>

class Resources {
private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
public:
	static SDL_Texture* GetImage (std::string file);
	static void ClearImages ();
};

#endif /* ENGINE_RESOURCES_H_ */
