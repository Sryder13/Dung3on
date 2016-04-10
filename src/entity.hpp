#ifndef ENTITY_H
#define ENTITY_H

#include<iostream>

#include "md2.hpp"
#include "controls.hpp"

class gamemap;

enum directions
{
	DIR_NORTH,
	DIR_EAST,
	DIR_SOUTH,
	DIR_WEST,
};

class entity
{
	public:
		float getRotationFromDirection(directions dir);

		entity(int x, int y, const std::string &modelFilename, gamemap *currentmap);
		int getX() {return this->x;}
		void setX(int x) {this->x = x;}
		int getY() {return this->y;}
		void setY(int y) {this->y = y;}
		void setEntityModel(const std::string &filename);
		directions getFacing() {return this->facing;}
		void setFacing(directions facing) {this->facing = facing;}

		virtual void update(gamemap *currentmap, controls gameControls) {

		}
		void renderEntity();
	protected:
	private:
		int x;
		int y;
		md2 *model;
		directions facing;
};

class player: public entity
{
	public:
		player(int x, int y, const std::string &modelFilename, gamemap *currentmap): entity(x, y, modelFilename, currentmap)
		{

		}
		void update(gamemap *currentmap, controls gameControls);
	protected:
	private:
};

#endif // ENTITY_H
