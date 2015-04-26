/*
 * TilePassable.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#include "TilePassable.h"

TilePassable::TilePassable(Rect hitBox, TileSet* tileSet, int tileIndex) :
		Tile(hitBox, tileSet, tileIndex) {

}

TilePassable::~TilePassable() {
}

void TilePassable::OnCollision(Player* player) {
	// Nada acontece feijoada
}
