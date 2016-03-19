#ifndef GAMEMAP_H
#define GAMEMAP_H

#include<iostream>

#include "md2.hpp"

#define MAP_X_SIZE 64
#define MAP_Y_SIZE 64

// enum for the types of tiles there are
enum tile_types
{
	TILE_FLOOR,
	TILE_WALL,
	TILE_STAIRS,
};

enum directions
{
	DIR_NORTH,
	DIR_EAST,
	DIR_SOUTH,
	DIR_WEST,
};

class tile
{
	public:
		tile();
		tile_types getTileType() {return tileType;}
		void setTileType(tile_types tileType) {this->tileType = tileType;}
		md2 *getTileModel() {return model;}
		void setTileModel(const std::string &filename);
		float getRotation() {return rotation;}
		float setRotation(float rotation) {this->rotation = rotation;}
	protected:
	private:
		tile_types tileType;
		md2 *model;
		float rotation;
};

class gamemap
{
	public:
		void generateMap();
		void renderMap();
	protected:
	private:
		bool dirIsType(directions direction, tile_types tileType, int x, int y);
		std::string floorTileModels(int x, int y);
		void setTilesModels();

		tile tiles[MAP_X_SIZE][MAP_Y_SIZE];
};

#endif // GAMEMAP_H
