/*
 * TileMap.cpp
 *
 *  Created on: 01/04/2015
 *      Author: Pedro
 */

#include "TileMap.h"

#include <string>
#include <stdio.h>
#include <math.h>
#include <iostream>

TileMap::TileMap(std::string file, TileSet* tileSet) {
	this->tileSet = tileSet;
	Load(file);
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
	for (int i = 0; i < mapDepth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			for (int k = 0; k < mapWidth; k++) {
				fscanf(fp, "%d", &index);
				fscanf(fp, "%c", &comma);

				Tile* tile;
				Rect tileRect;
				tileRect.SetX(j * tileSet->GetTileWidth());
				tileRect.SetY(k * tileSet->GetTileHeight());
				tileRect.SetH(tileSet->GetTileHeight());
				tileRect.SetW(tileSet->GetTileWidth());

				if (index != 0 && i == mapDepth - 1) {
					TileSolid* tileSolid = new TileSolid(tileRect, tileSet, index);
					tile = tileSolid;
				} else {
					TilePassable* tilePass = new TilePassable(tileRect, tileSet, index);
					tile = tilePass;
				}

				tileMatrix.push_back(tile);
			}
		}
	}

	/*
	for (int i = 0; i < mapWidth*mapHeight*mapDepth; i++){
		fscanf(fp, "%d", &index);
		fscanf(fp, "%c", &comma);
		tileMatrix.push_back(index);
	}
	*/
}

void TileMap::SetTileSet(TileSet* tileSet) {
	this->tileSet = tileSet;
}

Tile* TileMap::At(int x, int y, int z) {
	return tileMatrix[(mapWidth*y + x) + (mapWidth*mapHeight*z)];
}

void TileMap::Render(int layer, float parallaxFactor, int cameraX, int cameraY) {
	float parallax = 1 + layer*parallaxFactor;
	for(int h = 0; h < mapHeight; h++){
		for(int w = 0; w < mapWidth; w++){
			tileSet->Render(At(w, h, layer)->GetTileIndex(), w*(tileSet->GetTileWidth()) + cameraX*parallax, h*(tileSet->GetTileHeight()) + cameraY*parallax);
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

void TileMap::PositionToIndex(float x, float y, int* i, int* j) {
	*i = (int) floor(y / this->tileSet->GetTileHeight());
	*j = (int) floor(x / this->tileSet->GetTileWidth());
}

void TileMap::Sort(CollidingTile* collidingTiles, int size) {
	bool trocou = true;
	while (trocou) {
		trocou = false;
		for (int i = 0; i < size - 1; i++) {
			if (collidingTiles[i].distanceToPlayer
					> collidingTiles[i + 1].distanceToPlayer) {
				trocou = true;
				CollidingTile temp;
				temp = collidingTiles[i];
				collidingTiles[i] = collidingTiles[i + 1];
				collidingTiles[i + 1] = temp;
			}
		}
	}
}

void TileMap::CheckCollision(Player* player) {
	CollidingTile collidingTiles[30];
	int n = 0;
	int line, column;

	std::cout << "2.5.1" << std::endl;
	player->SetOnGround(false);

	std::cout << "2.5.2" << std::endl;
	PositionToIndex(player->GetBox().GetX(), player->GetBox().GetY(), &line, &column);
	std::cout << "2.5.3" << std::endl;
	for (int i = std::max(0, line - 1); i <= std::min(mapHeight - 1, line + 1); i++) {
		for (int j = std::max(0, column - 1); j <= std::min(mapWidth - 1, column + 1); j++) {
			Tile* tile = At(mapDepth - 1, i, j);
			std::cout << "2.5.4" << std::endl;
			if (tile->CollidesWith(player)) {
				std::cout << "2.5.5" << std::endl;
				CollidingTile temp;
				Point playerPoint(player->GetBox().GetX(), player->GetBox().GetY());
				Point tilePoint(tile->GetBox().GetX(), tile->GetBox().GetY());
				temp.distanceToPlayer = playerPoint.distance(tilePoint);
				temp.tile = tile;
				std::cout << "2.5.6" << std::endl;
				collidingTiles[n] = temp;
				n++;
				std::cout << "2.5.7" << std::endl;
			}
		}
	}

	Sort(collidingTiles, n);
	std::cout << "2.5.8" << std::endl;
	for (int i = 0; i < n; i++) {
		(collidingTiles[i]).tile->OnCollision(player);
		std::cout << "2.5.9" << std::endl;
	}
}
