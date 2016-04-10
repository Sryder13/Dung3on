#include "entity.hpp"
#include "gamemap.hpp"

float entity::getRotationFromDirection(directions dir)
{
	switch (dir)
	{
		case DIR_NORTH:
			return 0.0f;
		case DIR_EAST:
			return 90.0f;
		case DIR_SOUTH:
			return 180.0f;
		case DIR_WEST:
			return 270.0f;
	}
	return 0.0f;
}

entity::entity(int x, int y, const std::string &modelFilename, gamemap *currentmap)
{
	setX(x);
	setY(y);
	setFacing(DIR_NORTH);
	setEntityModel(modelFilename);
}

void entity::setEntityModel(const std::string &filename)
{
	model = resourcemanager::getResourceManager()->getResource<md2>(filename);
}

void entity::renderEntity()
{
	vec3 position = {x, 0.0f, y};
	model->renderFrame(0, position, getRotationFromDirection(facing), "./asset/texture/enemy_test.png");
}

void player::update(gamemap *currentmap, controls gameControls)
{
	if (gameControls.getPressedButtons() & BUTTON_UP && !(gameControls.getHeldButtons() & BUTTON_UP))
	{
		if (!currentmap->dirIsType(DIR_NORTH, TILE_WALL, getX(), getY()))
		{
			setY(getY()-1);
			setFacing(DIR_NORTH);
		}
	}
	else if (gameControls.getPressedButtons() & BUTTON_RIGHT && !(gameControls.getHeldButtons() & BUTTON_RIGHT))
	{
		if (!currentmap->dirIsType(DIR_EAST, TILE_WALL, getX(), getY()))
		{
			setX(getX()+1);
			setFacing(DIR_EAST);
		}
	}
	else if (gameControls.getPressedButtons() & BUTTON_DOWN && !(gameControls.getHeldButtons() & BUTTON_DOWN))
	{
		if (!currentmap->dirIsType(DIR_SOUTH, TILE_WALL, getX(), getY()))
		{
			setY(getY()+1);
			setFacing(DIR_SOUTH);
		}
	}
	else if (gameControls.getPressedButtons() & BUTTON_LEFT && !(gameControls.getHeldButtons() & BUTTON_LEFT))
	{
		if (!currentmap->dirIsType(DIR_WEST, TILE_WALL, getX(), getY()))
		{
			setX(getX()-1);
			setFacing(DIR_WEST);
		}
	}

	if (currentmap->tileIsType(TILE_STAIRS, getX(), getY()))
		currentmap->generateMap();
}
