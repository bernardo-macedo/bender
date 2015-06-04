/*
 * Tile.h
 *
 *  Created on: Jun 2, 2015
 *      Author: -Bernardo
 */

#ifndef ENGINE_TILESET_TILE_H_
#define ENGINE_TILESET_TILE_H_

#include "../Geometry/Rect.h"

class Tile {
private:
	int index;
	Rect box;
public:
	Tile(int index, Rect box);
	virtual ~Tile();

	int GetIndex();
	Rect GetBox();
};

#endif /* ENGINE_TILESET_TILE_H_ */
