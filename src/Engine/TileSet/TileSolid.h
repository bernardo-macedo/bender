/*
 * TileSolid.h
 *
 *  Created on: 26/12/2013
 *      Author: vitor
 */

#ifndef TILESOLID_H_
#define TILESOLID_H_

#include "Tile.h"
#include "../Geometry/Rect.h"
#include <math.h>

class TileSolid: public Tile {
public:
	TileSolid(Rect hitBox, TileSet* tileSet, int tileIndex);
	virtual ~TileSolid();

	void OnCollision(Player* player);
};

#endif /* TILESOLID_H_ */
