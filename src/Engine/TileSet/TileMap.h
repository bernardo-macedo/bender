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
#include "Tile.h"
#include "TileSolid.h"
#include "TilePassable.h"
#include "../Player.h"

class TileMap {
private:
	class CollidingTile {
	public:
		float distanceToPlayer;
		Tile* tile;
	};
private:
	std::vector<Tile*> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;

	void PositionToIndex(float x, float y, int* i, int* j);
	void Sort(CollidingTile* collidingTiles, int size);
public:
	TileMap (std::string file, TileSet* tileSet);
	void Load (std::string file);
	void SetTileSet (TileSet* tileSet);
	Tile* At (int x, int y, int z = 0);
	void Render (int layer, float parallaxFactor, int cameraX = 0, int cameraY = 0);
	int GetWidth ();
	int GetHeight ();
	int GetDepth ();
	void CheckCollision(Player* player);
};

#endif /* ENGINE_TILESET_TILEMAP_H_ */
