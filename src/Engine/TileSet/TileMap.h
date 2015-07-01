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
#include <sstream>
#include <fstream>
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
	int extraCollisionLayerIndex ;
	int mapScale ;
	std::multimap<float, Tile> tileCollisions;
	std::multimap<float, Tile> extraTileCollisions;
	std::vector<int> groundTileIndexes;

	void GetTileMatrixIndexesAtPos(float x, float y, int* i, int* j);
	std::vector<std::pair<int, Rect>> GetTilesSurroundingRect(Rect rect, int layerIndex);
	void LoadMapGrounds(std::string file);

public:
	TileMap (std::string file, int collisionLayerIndex, int mapScale = 1);
	virtual ~TileMap();
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
	void SetExtraCollisionLayer(int layer);
};

#endif /* ENGINE_TILESET_TILEMAP_H_ */
