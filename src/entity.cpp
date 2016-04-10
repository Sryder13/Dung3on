#include "entity.hpp"

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

void player::update(gamemap *currentmap)
{

}
