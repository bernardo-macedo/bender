/*
 * TileMap.cpp
 *
 *  Created on: 01/04/2015
 *      Author: Pedro
 */

#include "TileMap.h"

#include <string>
#include <stdio.h>

TileMap::TileMap(std::string file, TileSet* tileSet) {
	Load(file);
	this->tileSet = tileSet;
}

void TileMap::Load(std::string file) {
	char comma;
	FILE *fp = fopen(file.c_str(), "r");
	fscanf(fp, "%d", &(this->mapWidth));
	fscanf(fp, "%c", &comma);
	fscanf(fp, "%d", &(this->mapHeight));
	fscanf(fp, "%c", &comma);
	fscanf(fp, "%d", &(this->mapDepth));
	fscanf(fp, "%c", &comma);

	int index;
	for (int i = 0; i < mapWidth*mapHeight*mapDepth; i++){
		fscanf(fp, "%d", &index);
		fscanf(fp, "%c", &comma);
		tileMatrix.push_back(index);
	}
}

void TileMap::SetTileSet(TileSet* tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
	return tileMatrix[(mapWidth*y + x) + (mapWidth*mapHeight*z)];
}

void TileMap::Render(int layer, float parallaxFactor, int cameraX, int cameraY) {
	float parallax = 1 + layer*parallaxFactor;
	for(int j = 0; j < mapHeight; j++){
		for(int h = 0; h < mapWidth; h++){
			tileSet->Render(At(h, j, layer), h*(tileSet->GetTileWidth()) + cameraX*parallax, j*(tileSet->GetTileHeight()) + cameraY*parallax);
		}
	}
}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}
