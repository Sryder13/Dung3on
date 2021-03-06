#ifndef GAMEMAP_H
#define GAMEMAP_H

#include<iostream>
#include<cstdlib>
#include<vector>
#include<list>

#include "md2.hpp"
#include "entity.hpp"
#include "controls.hpp"

#define MAP_X_SIZE 64
#define MAP_Y_SIZE 64

#define ROOMS_MAX 10
#define ROOM_MAX_X 10
#define ROOM_MAX_Y 10
#define ROOM_MIN_X 3
#define ROOM_MIN_Y 3

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
		tile();
		tile_types getTileType() {return tileType;}
		void setTileType(tile_types tileType) {this->tileType = tileType;}
		md2 *getTileModel() {return model;}
		void setTileModel(const std::string &filename);
		float getRotation() {return rotation;}
		void setRotation(float rotation) {this->rotation = rotation;}
	protected:
	private:
		tile_types tileType;
		md2 *model;
		float rotation;
};

// For now, rooms are a temporarily created class that is made during dungeon creation
// They may be stored in the map later, but for now there is no need
class room
{
	public:
		room(int x, int y, int w, int h) {this->x = x; this->y = y; this->w = w; this->h = h;}
		bool intersects(const room *room2)
		{
			if (this->x <= room2->x + room2->w && this->x + this->w >= room2->x
				&& this->y <= room2->y + room2->h && this->y + this->h >= room2->y)
				return true;
			else
				return false;
		}
		int getX() {return this->x;}
		int getY() {return this->y;}
		int getW() {return this->w;}
		int getH() {return this->h;}
	protected:
	private:
		int x;
		int y;
		int w;
		int h;
};

class gamemap
{
	public:
		void generateMap();
		void renderMap();
		void updateEntities(controls gameControls);
		bool tileIsType(tile_types tileType, int x, int y);
		bool dirIsType(directions direction, tile_types tileType, int x, int y);
		virtual ~gamemap();
		entity *getFirstEntity() {return *(entityList.begin());}
	protected:
	private:
		std::string floorTileModels(int x, int y);
		void setTilesModels();
		void addRoom(int x, int y, int w, int h);
		void addHCorridor(int y, int x1, int x2);
		void addVCorridor(int x, int y1, int y2);

		tile tiles[MAP_X_SIZE][MAP_Y_SIZE];
		std::list<entity*> entityList;
};

#endif // GAMEMAP_H
