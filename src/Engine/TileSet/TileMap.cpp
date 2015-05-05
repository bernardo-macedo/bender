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
			tileSet->Render(At(h, j, layer), h*(tileSet->GetTileWidth()) - cameraX*parallax, j*(tileSet->GetTileHeight()) - cameraY*parallax);
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

int TileMap::collides(Minion* minion, int layer, Point* colPoint){
	double w, h, centerAx,centerBx, centerAy, centerBy, dx, dy, wy, hx;
	int xT, yT, xBoxScreen, yBoxScreen;
	int start = layer*mapHeight*mapWidth;
	for(int i = start; i < start + 625; i++){
		if(tileMatrix[i] > 0){
			xT = (i - start) % mapWidth;
			yT = (i - start) / mapWidth;
			xBoxScreen = xT*tileSet->GetTileWidth();
			yBoxScreen = yT*tileSet->GetTileHeight();
			w = 0.5 * (minion->GetBox().GetW() + tileSet->GetTileWidth());
			h = 0.5 * (minion->GetBox().GetH() + tileSet->GetTileHeight());

			centerAx = minion->GetBox().GetX();
			centerAy = minion->GetBox().GetY();
			centerBx = xBoxScreen + (tileSet->GetTileWidth() / 2);
			centerBy = yBoxScreen + (tileSet->GetTileHeight() / 2);

			dx = centerAx - centerBx;
			dy = centerAy - centerBy;

			std::cout << yT<< std::endl;

			if (abs(dx) <= w && abs(dy) <= h){
				/* collision! */
				wy = w * dy;
				hx = h * dx;
				if (wy > hx){
					if (wy > -hx){
						colPoint->setX(xBoxScreen);
						colPoint->setY(yBoxScreen + tileSet->GetTileHeight());
						return Rect::TOP;
					}
					else{
						colPoint->setX(xBoxScreen + tileSet->GetTileWidth());
						colPoint->setY(yBoxScreen);
						return Rect::LEFT;
					}
				}
				else{
					if (wy > -hx){
						colPoint->setX(xBoxScreen);
						colPoint->setY(yBoxScreen);
						return Rect::RIGHT;
					}
					else{
						colPoint->setX(xBoxScreen);
						colPoint->setY(yBoxScreen);
						return Rect::BOTTOM;
					}
				}
			}
		}
	}
	return Rect::NONE;
}
