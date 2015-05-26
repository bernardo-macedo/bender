/*
 * TileMap.h
 *
 *  Created on; 01/04/2015
 *      Author; Pedro
 */

#ifndef ENGINE_TILESET_TILEMAP_H_
#define ENGINE_TILESET_TILEMAP_H_

#include <iostream>
#include <vector>
#include "TileSet.h"
#include "../../Baon.h"

class TileMap {
private:
	std::vector<int> tileMatrix ;
	TileSet* tileSet ;
	int mapWidth ;
	int mapHeight ;
	int mapDepth ;
public:
	TileMap (std::string file);
	void Load (std::string file);
	void SetTileSet (TileSet* tileSet);
	int& At (int x, int y, int z = 0);
	void Render (int layer, float parallaxFacotr, int cameraX = 0, int cameraY = 0);
	int GetWidth ();
	int GetHeight ();
	int GetDepth ();
	void CheckCollisions(Baon* being);
};

#endif /* ENGINE_TILESET_TILEMAP_H_ */
