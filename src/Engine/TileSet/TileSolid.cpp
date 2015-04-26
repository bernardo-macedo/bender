/*
 * TileSolid.cpp
 *
 *  Created on: 26/12/2013
 *      Author: vitor
 */

#include "TileSolid.h"

TileSolid::TileSolid(Rect hitBox, TileSet* tileSet, int tileIndex) :
		Tile(hitBox, tileSet, tileIndex) {

}

TileSolid::~TileSolid() {
}

void TileSolid::OnCollision(Player* player) {
	Point overlap = player->GetBox().Intersection(this->box);

	if (fabs(overlap.getY()) > fabs(overlap.getX())) {
		overlap.setY(0);
	} else {
		overlap.setX(0);
		if (player->GetBox().GetY() < this->box.GetY()) {
			player->SetOnGround(true);
		}
	}
	player->GetBox().SetX(player->GetBox().GetX() + overlap.getX());
	player->GetBox().SetY(player->GetBox().GetY() + overlap.getY());
}
