#include "gamemap.hpp"

tile::tile()
{
	tileType = TILE_WALL;
	model = resourcemanager::getResourceManager()->getResource<md2>("./asset/model/sphere_test.md2"); // use this model as a "not set" model
	rotation = 0.0f;
}

void tile::setTileModel(const std::string &filename)
{
	model = resourcemanager::getResourceManager()->getResource<md2>(filename);
}

void gamemap::generateMap()
{
	// Clear the map
    for (int x = 0; x < MAP_X_SIZE; x++)
    {
		for (int y = 0; y < MAP_Y_SIZE; y++)
		{
			tiles[x][y].setTileType(TILE_WALL);
			tiles[x][y].setRotation(0.0f);
		}
    }

    // place rooms
    std::list<room> roomsList;

    for (int i = 0; i < ROOMS_MAX; i++)
    {
        int w = ROOM_MIN_X + rand() % (ROOM_MAX_X - ROOM_MIN_X + 1);
        int h = ROOM_MIN_Y + rand() % (ROOM_MAX_Y - ROOM_MIN_Y + 1);
        int x = rand() % (MAP_X_SIZE - w - 16) + 8;
        int y = rand() % (MAP_Y_SIZE - h - 16) + 8;

        room newRoom = room(x, y, w, h);

        int failed = false;

        for (std::list<room>::iterator roomsList_iter = roomsList.begin(); roomsList_iter != roomsList.end(); roomsList_iter++)
        {
			if (newRoom.intersects(&(*roomsList_iter)))
			{
				failed = true;
				break;
			}
        }
        if (!failed)
		{
			roomsList.push_back(newRoom);

			addRoom(newRoom.getX(), newRoom.getY(), newRoom.getW(), newRoom.getH());
		}
    }

    setTilesModels();
}

void gamemap::addRoom(int x, int y, int w, int h)
{
	for (int i = x; i < x + w; i++)
	{
		for (int j = y; j < y + h; j++)
		{
			tiles[i][j].setTileType(TILE_FLOOR);
		}
	}
}

bool gamemap::dirIsType(directions direction, tile_types tileType, int x, int y)
{
	switch (direction)
	{
		case DIR_NORTH:
			return (tileType == TILE_WALL && y == 0) || tiles[x][y-1].getTileType() == tileType;
		case DIR_EAST:
			return (tileType == TILE_WALL && x == MAP_X_SIZE-1) || tiles[x+1][y].getTileType() == tileType;
		case DIR_SOUTH:
			return (tileType == TILE_WALL && y == MAP_Y_SIZE-1) || tiles[x][y+1].getTileType() == tileType;
		case DIR_WEST:
			return (tileType == TILE_WALL && x == 0) || tiles[x-1][y].getTileType() == tileType;
		default:
			break;
	}
	std::cout << "WARNING: gamemap::dirIsType: invalid direction" << std::endl;
	return false;
}

std::string gamemap::floorTileModels(int x, int y)
{
	std::string modelFile;
	int numSurroundingWalls = 0;
	if (x < 0 || x >= MAP_X_SIZE)
	{
		std::cout << "WARNING: gamemap::surroundingWallsNum: invalid map x position: " << x << std::endl;
		return 0;
	}

	if (y < 0 || y >= MAP_X_SIZE)
	{
		std::cout << "WARNING: gamemap::surroundingWallsNum: invalid map y position: " << y << std::endl;
		return 0;
	}

	if (dirIsType(DIR_NORTH, TILE_WALL, x, y))
		numSurroundingWalls++;
	if (dirIsType(DIR_EAST, TILE_WALL, x, y))
		numSurroundingWalls++;
	if (dirIsType(DIR_SOUTH, TILE_WALL, x, y))
		numSurroundingWalls++;
	if (dirIsType(DIR_WEST, TILE_WALL, x, y))
		numSurroundingWalls++;

	if (numSurroundingWalls == 0)
		modelFile = "./asset/model/tile_0.md2";
	else if (numSurroundingWalls == 1)
	{
		modelFile = "./asset/model/tile_1.md2";
		if (dirIsType(DIR_EAST, TILE_WALL, x, y))
			tiles[x][y].setRotation(270.0f);
		else if (dirIsType(DIR_SOUTH, TILE_WALL, x, y))
			tiles[x][y].setRotation(180.0f);
		else if (dirIsType(DIR_WEST, TILE_WALL, x, y))
			tiles[x][y].setRotation(90.0f);
	}
	else if (numSurroundingWalls == 2)
	{
		modelFile = "./asset/model/tile_2.md2";
		if (dirIsType(DIR_EAST, TILE_WALL, x, y) && dirIsType(DIR_NORTH, TILE_WALL, x, y))
			tiles[x][y].setRotation(270.0f);
		else if (dirIsType(DIR_EAST, TILE_WALL, x, y) && dirIsType(DIR_SOUTH, TILE_WALL, x, y))
			tiles[x][y].setRotation(180.0f);
		else if (dirIsType(DIR_WEST, TILE_WALL, x, y) && dirIsType(DIR_SOUTH, TILE_WALL, x, y))
			tiles[x][y].setRotation(90.0f);
	}
	else if (numSurroundingWalls == 3)
	{
		modelFile = "./asset/model/tile_3.md2";
		if (dirIsType(DIR_NORTH, TILE_FLOOR, x, y))
			tiles[x][y].setRotation(90.0f);
		else if (dirIsType(DIR_SOUTH, TILE_FLOOR, x, y))
			tiles[x][y].setRotation(270.0f);
		else if (dirIsType(DIR_WEST, TILE_FLOOR, x, y))
			tiles[x][y].setRotation(180.0f);
	}
	else if (numSurroundingWalls == 4)
		modelFile = "./asset/model/tile_4.md2";

	// special case for corridors
	if (numSurroundingWalls == 2
		&& (x > 0 && x < MAP_X_SIZE-1 && (tiles[x-1][y].getTileType() == TILE_FLOOR && tiles[x+1][y].getTileType() == TILE_FLOOR)
		|| (y > 0 && y < MAP_Y_SIZE-1 && tiles[x][y-1].getTileType() == TILE_FLOOR && tiles[x][y+1].getTileType() == TILE_FLOOR)))
	{
		modelFile = "./asset/model/tile_corridor.md2";
		if (dirIsType(DIR_NORTH, TILE_FLOOR, x, y))
			tiles[x][y].setRotation(90.0f);
	}

	return modelFile;

}

void gamemap::setTilesModels()
{
	std::string modelFile;
    for (int x = 0; x < MAP_X_SIZE; x++)
    {
		for (int y = 0; y < MAP_Y_SIZE; y++)
		{
			switch (tiles[x][y].getTileType())
			{
				case TILE_FLOOR:
					// TODO (sean): determine tile rotation based on where walls are
					modelFile = floorTileModels(x, y);
					break;
				case TILE_WALL:
					modelFile = "./asset/model/tile_wall.md2";
					break;
				case TILE_STAIRS:
					modelFile = "./asset/model/tile_stairs.md2";
					break;
				default:
					std::cout << "gamemap::setTilesModels(): Unknown tile type on tile: X = " << x << ": Y = " << y << std::endl;
					break;
			}
			tiles[x][y].setTileModel(modelFile);
		}
    }
}

void gamemap::renderMap()
{
	for (int x = 0; x < MAP_X_SIZE; x++)
    {
		for (int y = 0; y < MAP_Y_SIZE; y++)
		{
			vec3 position = {x, 0.0f, y};
			tiles[x][y].getTileModel()->renderFrame(0, position, tiles[x][y].getRotation());
		}
	}
}
