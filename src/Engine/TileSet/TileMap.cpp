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

TileMap::TileMap(std::string file, int collisionLayerIndex, int mapScale) {
	Load(file);
	this->collisionLayerIndex = collisionLayerIndex;
	this->mapScale = mapScale;
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

Collision::CollisionSide TileMap::CheckCollisions(Rect rect) {
	bool collidedLeft = false;
	bool collidedRight = false;
	bool collidedTop = false;
	bool collidedBottom = false;
	Rect scaledRect;

	scaledRect.SetX(rect.GetX());
	scaledRect.SetY(rect.GetY());
	scaledRect.SetW(rect.GetW() * mapScale);
	scaledRect.SetH(rect.GetH() * mapScale);

	// pega tiles do layer de colisao
	std::vector<Rect> tilesToCheck = GetTilesSurroundingRect(scaledRect);
	// checa colisao com os tiles ao redor dele
	for (unsigned int i = 0; i < tilesToCheck.size(); i++) {
		Rect tile = tilesToCheck[i];
		if (Collision::IsColliding(tilesToCheck[i], scaledRect, 0, 0)) {
			// se houve colisao, verifica se foi no eixo x, no eixo y ou em ambos
			// Minkowski sum
			float wy = (rect.GetW() + tile.GetW()) * (rect.GetCenter().getY() - tile.GetCenter().getY());
			float hx = (rect.GetH() + tile.GetH()) * (rect.GetCenter().getX() - tile.GetCenter().getX());

			if (wy > hx) {
			    if (wy > -hx) {
			        /* top */
			    	collidedTop = true;
			    } else {
			        /* left */
			    	collidedLeft = true;
			    }
			} else {
			    if (wy > -hx) {
			        /* right */
			    	collidedRight = true;
			    } else {
			        /* bottom */
			    	collidedBottom = true;
			    }
			}
			//return true;
		}
	}
	//return false;
	return Collision::CollisionSide(collidedLeft, collidedRight, collidedTop, collidedBottom);




}

std::vector<Rect> TileMap::GetTilesSurroundingRect(Rect rect) {
	std::vector<Rect> tiles;
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
			int tileIndex = At(row, col, collisionLayerIndex);
			// o indice 90 eh erro do mapa
			if (tileIndex != 0 && tileIndex != 90) {
				// Cria Rect para estes tiles
				Rect tileRect;
				tileRect.SetX(row * tileSet->GetTileWidth() * mapScale);
				tileRect.SetY(col * tileSet->GetTileHeight() * mapScale);
				tileRect.SetW(tileSet->GetTileWidth() * mapScale);
				tileRect.SetH(tileSet->GetTileHeight() * mapScale);
				// Adiciona Rect na lista de retorno
				tiles.push_back(tileRect);
			}
		}
	}
	return tiles;

}

void TileMap::GetTileMatrixIndexesAtPos(float x, float y, int* i, int* j) {
	*i = (int) x/(tileSet->GetTileWidth() * mapScale);
	*j = (int) y/(tileSet->GetTileHeight() * mapScale);
}
