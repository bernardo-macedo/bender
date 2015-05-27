/*
 * TileMap.cpp
 *
 *  Created on: 01/04/2015
 *      Author: Pedro
 */

#include "TileMap.h"

#include <TmxImage.h>
#include <TmxLayer.h>
#include <TmxMap.h>
#include <TmxTileLayer.h>
#include <TmxTileset.h>
#include <cmath>
#include <string>

#include "../Game.h"

TileMap::TileMap(std::string file) {
	Load(file);
}

void TileMap::Load(std::string file) {
	Tmx::Map map;

	map.ParseFile(file);

	if (map.HasError()) {
		std::cout << "Nao foi possivel fazer parse do mapa : " << file <<
				"Erro: " << map.GetErrorText() << std::endl;
		return;
	}

	this->mapWidth = map.GetLayer(0)->GetWidth();
	this->mapHeight = map.GetLayer(0)->GetHeight();
	this->mapDepth = map.GetNumLayers();


	const Tmx::Tileset* tileSet = map.GetTileset(0);
	TileSet* localTileSet = new TileSet(tileSet->GetTileWidth(),
			tileSet->GetTileHeight(), "img/" + tileSet->GetImage()->GetSource());

	SetTileSet(localTileSet);

	int index;
	for (int i = 0; i < mapDepth; i++) {
		const Tmx::TileLayer* layer = map.GetTileLayer(i);
		std::cout << "i = " << i << " layer name = " << layer->GetName() << std::endl;
		for (int k = 0; k < mapHeight; k++) {
			for (int j = 0; j < mapWidth; j++) {
				index = layer->GetTileGid(j, k);
				tileMatrix.push_back(index);
			}
		}
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
		int min = std::max(0, (-cameraX)/(tileSet->GetTileWidth()*3) - 3);
		int max = std::min(mapWidth, 3 + (-cameraX + Game::SCREEN_WIDTH)/(tileSet->GetTileWidth()*3));
		std::cout << min << " " << max << " " << cameraX << std::endl;
		for(int h = min; h < max; h++){
			tileSet->Render(At(h, j, layer), h*(tileSet->GetTileWidth()) + cameraX*parallax/3, j*(tileSet->GetTileHeight()) + cameraY*parallax/3);
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

void TileMap::CheckCollisions(Baon* being) {
}
