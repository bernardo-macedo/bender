/*
 * Tile.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: -Bernardo
 */

#include "Tile.h"

Tile::~Tile() {
	// TODO Auto-generated destructor stub
}

Tile::Tile(int index, Rect box) {
	this->index = index;
	this->box = box;
}

int Tile::GetIndex() {
	return index;
}

Rect Tile::GetBox() {
	return box;
}
