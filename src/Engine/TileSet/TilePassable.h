/*
 * TilePassable.h
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#ifndef TILEPASSABLE_H_
#define TILEPASSABLE_H_

#include "Tile.h"
#include "../Player.h"

class TilePassable: public Tile {
public:
	TilePassable(Rect hitBox, TileSet* tileSet, int tileIndex);
	virtual ~TilePassable();

	void OnCollision(Player* player);
};

#endif /* TILEPASSABLE_H_ */
