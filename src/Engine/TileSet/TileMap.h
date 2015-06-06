/*
 * TileMap.h
 *
 *  Created on; 01/04/2015
 *      Author; Pedro
 */

#ifndef ENGINE_TILESET_TILEMAP_H_
#define ENGINE_TILESET_TILEMAP_H_

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "TileSet.h"
#include "../Geometry/Rect.h"
#include "../Geometry/Point.h"
#include "../../Baon.h"
#include "../Collision.h"
#include "Tile.h"

class TileMap {
private:
	std::vector<int> tileMatrix ;
	TileSet* tileSet ;
	int mapWidth ;
	int mapHeight ;
	int mapDepth ;
	int collisionLayerIndex ;
	int mapScale ;
	std::multimap<float, Tile> tileCollisions;

	void GetTileMatrixIndexesAtPos(float x, float y, int* i, int* j);
	std::vector<std::pair<int, Rect>> GetTilesSurroundingRect(Rect rect);

public:
	TileMap (std::string file, int collisionLayerIndex, int mapScale = 1);
	void Load (std::string file);
	void SetTileSet (TileSet* tileSet);
	int& At (int x, int y, int z = 0);
	void Render (int layer, float parallaxFacotr, int cameraX = 0, int cameraY = 0);
	int GetWidth ();
	int GetHeight ();
	int GetDepth ();
	float GetMapMax();

	bool CheckCollisions(Being* being);
	void ResolveTileCollisions(Being* being);

};

#endif /* ENGINE_TILESET_TILEMAP_H_ */
