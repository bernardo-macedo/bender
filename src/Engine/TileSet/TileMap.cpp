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
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <utility>

#include "../Game.h"

TileMap::TileMap(std::string file, int collisionLayerIndex, int mapScale) {
	this->collisionLayerIndex = collisionLayerIndex;
	this->extraCollisionLayerIndex = -1;
	this->mapScale = mapScale;
	Load(file);
	LoadMapGrounds(file);
}

TileMap::~TileMap() {
	delete tileSet;
}

void TileMap::Load(std::string file) {
	Tmx::Map map;

	map.ParseFile("map/" + file);

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
			tileSet->GetTileHeight(), "img/" + tileSet->GetImage()->GetSource(), mapScale);

	SetTileSet(localTileSet);

	int index;
	for (int i = 0; i < mapDepth; i++) {
		const Tmx::TileLayer* layer = map.GetTileLayer(i);
		std::cout << "layer " << i << " = " <<layer->GetName() << std::endl;
		for (int k = 0; k < mapHeight; k++) {
			for (int j = 0; j < mapWidth; j++) {
				index = layer->GetTileGid(j, k);
				tileMatrix.push_back(index);
			}
		}
	}
}

void TileMap::LoadMapGrounds(std::string file) {
	std::ifstream infile("map/mapgrounds.txt");
	std::string line;
	std::string mapName;
	while (std::getline(infile, line)) {
		std::istringstream iss(line);
	    if (!(iss >> mapName)) {
	    	break;
	    } else if (mapName == file) {
	    	int groundTileIndex;
	    	while (iss >> groundTileIndex) {
				groundTileIndexes.push_back(groundTileIndex);
			}
	    	break;
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
	int loadOffset = 3;
	float parallax = 1 + layer*parallaxFactor;
	for(int j = 0; j < mapHeight; j++){
		int min = std::max(0, (-cameraX)/(tileSet->GetTileWidth() * mapScale) - loadOffset);
		int max = std::min(mapWidth, loadOffset + (-cameraX + Game::SCREEN_WIDTH)/(tileSet->GetTileWidth() * mapScale));
		for(int h = min; h < max; h++){
			tileSet->Render(At(h, j, layer), h*(tileSet->GetTileWidth()) + cameraX*parallax/mapScale, j*(tileSet->GetTileHeight()) + cameraY*parallax/mapScale);
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

bool TileMap::CheckCollisions(Being* being) {
	Rect scaledRect = being->GetBox();
	bool hasCollided = false;

	scaledRect.SetW(scaledRect.GetW() * being->GetScale());
	scaledRect.SetH(scaledRect.GetH() * being->GetScale());

	// pega tiles do layer de colisao
	std::vector<std::pair<int, Rect>> tilesToCheck = GetTilesSurroundingRect(scaledRect, collisionLayerIndex);
	// checa colisao com os tiles ao redor dele
	for (unsigned int i = 0; i < tilesToCheck.size(); i++) {
		int tileIndex = tilesToCheck[i].first;
		Rect tile = tilesToCheck[i].second;
		if (Collision::IsColliding(tile, scaledRect, 0, 0)) {
			hasCollided = true;
			float diffx = scaledRect.GetX() - tile.GetX();
			float diffy = scaledRect.GetY() - tile.GetY();
			float distanceToPlayer =  sqrt((diffx * diffx) + (diffy * diffy));
			tileCollisions.insert(std::make_pair(distanceToPlayer, Tile(tileIndex, tile)));
		}
	}

	if (extraCollisionLayerIndex != -1) {
		// pega tiles do layer extra de colisao
		std::vector<std::pair<int, Rect>> tilesToCheck = GetTilesSurroundingRect(scaledRect, extraCollisionLayerIndex);
		// checa colisao com os tiles ao redor dele
		for (unsigned int i = 0; i < tilesToCheck.size(); i++) {
			int tileIndex = tilesToCheck[i].first;
			Rect tile = tilesToCheck[i].second;
			if (Collision::IsColliding(tile, scaledRect, 0, 0)) {
				hasCollided = true;
				float diffx = scaledRect.GetX() - tile.GetX();
				float diffy = scaledRect.GetY() - tile.GetY();
				float distanceToPlayer =  sqrt((diffx * diffx) + (diffy * diffy));
				extraTileCollisions.insert(std::make_pair(distanceToPlayer, Tile(tileIndex, tile)));
			}
		}
	}

	return hasCollided;
}

void TileMap::ResolveTileCollisions(Being* being) {
	float intersectionX;
	Rect scaledRect = being->GetBox();

	scaledRect.SetW(scaledRect.GetW() * being->GetScale());
	scaledRect.SetH(scaledRect.GetH() * being->GetScale());

	std::multimap<float, Tile>::iterator it;

	// Resolve colisoes do layer principal
	for(it = tileCollisions.begin(); it != tileCollisions.end(); ++it) {
		Tile tile = it->second;
		Point overlap = scaledRect.Intersection(tile.GetBox());

		if (fabs(overlap.getY()) > fabs(overlap.getX())) {
			being->GetBody()->SetVelX(0);
			if (overlap.getX() > 0) {
				// colidiu com a borda esquerda do player
				intersectionX = (tile.GetBox().GetX() + tile.GetBox().GetW()) - scaledRect.GetX();
				scaledRect.SetX(scaledRect.GetX() + intersectionX + 1);
				being->NotifyTileCollision();
			} else if (overlap.getX() < 0) {
				// colidiu com a borda direita do player
				intersectionX = (scaledRect.GetX() + scaledRect.GetW()) - tile.GetBox().GetX();
				scaledRect.SetX(scaledRect.GetX() - intersectionX - 1);
				being->NotifyTileCollision();
				std::cout << "depois y = " << being->GetBox().GetY() << std::endl;
			}

		} else {
			float distY = scaledRect.GetY() - tile.GetBox().GetY();

			if (distY < 0 && fabs(distY) > (4 * scaledRect.GetH()/5)
					&& std::find(groundTileIndexes.begin(), groundTileIndexes.end(), tile.GetIndex()) != groundTileIndexes.end()) {
				being->GetBody()->SetVelY(0);
				scaledRect.SetY(tile.GetBox().GetY() - scaledRect.GetH());
				being->NotifyTileCollision();
			}
		}

		being->GetBody()->SetX(scaledRect.GetX());
		being->GetBody()->SetY(scaledRect.GetY());
	}
	tileCollisions.clear();

	// Resolve colisoes do layer secundario
	for(it = extraTileCollisions.begin(); it != extraTileCollisions.end(); ++it) {
		Tile tile = it->second;
		Point overlap = scaledRect.Intersection(tile.GetBox());

		if (fabs(overlap.getY()) >= fabs(overlap.getX())) {

			float distY = scaledRect.GetY() - tile.GetBox().GetY();
			// tileIndex = 5 eh um erro do mapa
			if (distY < 0 && fabs(distY) > (4 * scaledRect.GetH()/5) && tile.GetIndex() != 5) {
				being->GetBody()->SetVelY(0);
				scaledRect.SetY(tile.GetBox().GetY() - scaledRect.GetH());
				being->NotifyTileCollision();
			}

		}
		being->GetBody()->SetY(scaledRect.GetY());
	}
	extraTileCollisions.clear();
}

std::vector<std::pair<int, Rect>> TileMap::GetTilesSurroundingRect(Rect rect, int layerIndex) {
	std::vector<std::pair<int, Rect>> tiles;
	int centerX, centerY;

	// pega centro do player em coordenadas matriciais
	Point center = rect.GetCenter();
	GetTileMatrixIndexesAtPos(center.getX(), center.getY(), &centerX, &centerY);

	// pega lista dos tiles que possivelmente estao colidindo
	int rangeTilesX = ceil(rect.GetW()/(tileSet->GetTileWidth() * mapScale)) + 1;
	int rangeTilesY = ceil(rect.GetH()/(tileSet->GetTileHeight() * mapScale)) + 1;

	int minMatrixIndexRow = centerX - floor(rangeTilesX/2);
	int maxMatrixIndexRow = centerX + ceil(rangeTilesX/2);
	int minMatrixIndexCol = centerY - floor(rangeTilesY/2);
	int maxMatrixIndexCol = centerY + ceil(rangeTilesY/2);

	for (int row = std::max(0, minMatrixIndexRow); row <= std::min(mapWidth, maxMatrixIndexRow);  row++) {
		for (int col = std::max(0, minMatrixIndexCol); col <= std::min(mapHeight, maxMatrixIndexCol); col++) {
			// seleciona apenas os tiles com indice != 0
			int tileIndex = At(row, col, layerIndex);
			if (tileIndex != 0) {
				// Cria Rect para estes tiles
				Rect tileRect;
				tileRect.SetX(row * tileSet->GetTileWidth() * mapScale);
				tileRect.SetY(col * tileSet->GetTileHeight() * mapScale);
				tileRect.SetW(tileSet->GetTileWidth() * mapScale);
				tileRect.SetH(tileSet->GetTileHeight() * mapScale);
				// Adiciona Rect na lista de retorno
				tiles.push_back(std::make_pair(tileIndex, tileRect));
			}
		}
	}
	return tiles;

}

void TileMap::GetTileMatrixIndexesAtPos(float x, float y, int* i, int* j) {
	*i = (int) x/(tileSet->GetTileWidth() * mapScale);
	*j = (int) y/(tileSet->GetTileHeight() * mapScale);
}

float TileMap::GetMapMax() {
	return (tileSet->GetTileWidth() * mapScale) * (mapWidth);
}

void TileMap::SetExtraCollisionLayer(int layer) {
	this->extraCollisionLayerIndex = layer;
}
