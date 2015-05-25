/*
 * TileSet.cpp
 *
 *  Created on: 01/04/2015
 *      Author: Pedro
 */

#include "TileSet.h"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	tileSet = new Sprite(file);
	this->columns = tileSet->GetWidth()/this->tileWidth;
	this->rows = tileSet->GetHeight()/this->tileHeight;
	std::cout << "file = " << file.c_str() << std::endl;
	std::cout << "sprite getWidth = " << tileSet->GetWidth() << std::endl;
	std::cout << "sprite getHeight = " << tileSet->GetHeight() << std::endl;
	std::cout << "tileWidth = " << tileWidth << " tileHeight = " << tileHeight << std::endl;
	std::cout << "rows = " << rows << " columns = " << columns << std::endl;
}

void TileSet::Render(int index, float x, float y) {
	float xt, yt;
	if(index > (rows*columns - 1)){
		std::cout << "Indice max = " << rows*columns - 1 << std::endl;
		std::cout << "Indice invalido = " << index << std::endl;
		throw INDEX_OUT_OF_RANGE;
	}
	else{
		xt = (index-1) % columns;
		yt = (index-1) / columns;
		tileSet->SetClip(xt*tileWidth, yt*tileHeight, tileWidth, tileHeight);
		if(index > 0){
			tileSet->Render(x, y);
		}
	}
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}
