/*
 * Tile.h
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#ifndef TILE_H_
#define TILE_H_

#include "TileSet.h"
#include "../Sprite.h"
#include "../Player.h"
#include "../Geometry/Rect.h"

class Tile {
protected:
	Rect box;
	TileSet* tileSet;
	int tileIndex;

public:
	Tile(Rect hitBox, TileSet* tileSet, int tileIndex);
	virtual ~Tile();

	virtual bool CollidesWith(Player* player);
	virtual void OnCollision(Player* player) = 0;
	void Render(float cameraX, float cameraY);

	int GetTileIndex() {
		return tileIndex;
	}

	Rect GetBox() {
		return box;
	}
};

#endif /* TILE_H_ */
