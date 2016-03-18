#ifndef GAMEMAP_H
#define GAMEMAP_H

#include<iostream>

#include "md2.hpp"

#define MAP_X_SIZE 50
#define MAP_Y_SIZE 50

// enum for the types of tiles there are
enum tile_types
{
	TILE_FLOOR,
	TILE_WALL,
	TILE_STAIRS,
};

class tile
{
	public:
		tile_types getTileType() {return tileType;}
		void setTileType(tile_types tileType) {this->tileType = tileType;}
		md2 *getTileModel() {return model;}
		void setTileModel(const std::string &filename);
	protected:
	private:
		tile_types tileType;
		md2 *model;
};

class gamemap
{
	public:
		void generateMap();
		void renderMap();
	protected:
	private:
		int surroundingWallsNum(int x, int y);
		void setTilesModels();

		tile tiles[MAP_X_SIZE][MAP_Y_SIZE];
};

#endif // GAMEMAP_H
