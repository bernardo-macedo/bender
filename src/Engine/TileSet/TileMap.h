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
#include "../GameObject.h"
#include "../../Minion.h"

class TileMap {
private:
	std::vector<int> tileMatrix ;
	TileSet* tileSet ;
	int mapWidth ;
	int mapHeight ;
	int mapDepth ;
public:
	TileMap (std::string file, TileSet* tileSet);
	void Load (std::string file);
	void SetTileSet (TileSet* tileSet);
	int& At (int x, int y, int z = 0);
	void Render (int layer, float parallaxFacotr, int cameraX = 0, int cameraY = 0);
	int GetWidth ();
	int GetHeight ();
	int GetDepth ();
	bool* collides(Minion* minion, int layer, bool *colPos);
};

#endif /* ENGINE_TILESET_TILEMAP_H_ */
