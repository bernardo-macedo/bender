/*
 * TileSet.cpp
 *
 *  Created on: 01/04/2015
 *      Author: Pedro
 */

#include "TileSet.h"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file, int tileSetScale) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->tileSetScale = tileSetScale;
	tileSet = new Sprite(file);
	tileSet->SetScaleX(tileSetScale);
	tileSet->SetScaleY(tileSetScale);
	this->columns = tileSet->GetWidth()/(this->tileWidth*tileSetScale);
	this->rows = tileSet->GetHeight()/(this->tileHeight*tileSetScale);
}

void TileSet::Render(int index, float x, float y) {
	float xt, yt;
	if(index > (rows*columns)){
		std::cout << "index = " << index << " rows = " << rows << " columns = " << columns << std::endl;
		throw INDEX_OUT_OF_RANGE;
	}
	else{
		xt = ((index-1) % columns);
		yt = ((index-1) / columns);
		tileSet->SetClip(xt * tileWidth, yt * tileHeight, tileWidth, tileHeight);
		if(index > 0){
			tileSet->Render(x * tileSetScale, y * tileSetScale);
		}
	}
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}
