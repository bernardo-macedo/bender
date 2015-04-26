/*
 * Tile.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#include "Tile.h"

Tile::Tile(Rect hitBox, TileSet* tileSet, int tileIndex) :
		box(hitBox), tileIndex(tileIndex) {
	this->tileSet = tileSet;
}

Tile::~Tile() {
}

bool Tile::CollidesWith(Player* player) {
	return box.CollidesWith(player->GetBox());
	// return box.CollidesWith(player->getHitbox());
}

void Tile::Render(float cameraX, float cameraY) {
	if (tileIndex != -1) {
		tileSet->Render(tileIndex, box.GetX() - cameraX, box.GetY() - cameraY);
	}
}
