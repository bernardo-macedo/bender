/*
 * TileSet.h
 *
 *  Created on: 01/04/2015
 *      Author: Pedro
 */

#ifndef ENGINE_TILESET_TILESET_H_
#define ENGINE_TILESET_TILESET_H_

#include <iostream>
#include "../Sprite.h"

class TileSet {
private:
	Sprite* tileSet;
	int rows;
	int columns;
	int tileWidth;
	int tileHeight;
public:
	TileSet();
	TileSet (int tileWidth,	int tileHeight, std::string file);
	void Render (int index, float x, float y);
	int GetTileWidth ();
	int GetTileHeight();
};

#endif /* ENGINE_TILESET_TILESET_H_ */
