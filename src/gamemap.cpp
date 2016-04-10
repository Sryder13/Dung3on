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
			entityList.clear();
		}
	}

	// place rooms
	std::vector<room> roomsVector;
	int numRooms = 0;

	for (int i = 0; i < ROOMS_MAX; i++)
	{
		int w = ROOM_MIN_X + rand() % (ROOM_MAX_X - ROOM_MIN_X + 1);
		int h = ROOM_MIN_Y + rand() % (ROOM_MAX_Y - ROOM_MIN_Y + 1);
		int x = rand() % (MAP_X_SIZE - w - 16) + 8;
		int y = rand() % (MAP_Y_SIZE - h - 16) + 8;

		room newRoom = room(x, y, w, h);

		int failed = false;

		for (std::vector<room>::iterator roomsVector_iter = roomsVector.begin(); roomsVector_iter != roomsVector.end(); roomsVector_iter++)
		{
			if (newRoom.intersects(&(*roomsVector_iter)))
			{
				failed = true;
				break;
			}
		}
		if (!failed)
		{
			room *prevRoom = NULL;

			roomsVector.push_back(newRoom);
			if (roomsVector.size() > 1)
			{
				prevRoom = (&roomsVector.end()[-2]);
			}

			addRoom(newRoom.getX(), newRoom.getY(), newRoom.getW(), newRoom.getH());
			numRooms++;

			if (prevRoom)
			{
				if (rand() % 2) // carve out horizontally first
				{
					int y1 = (rand() % prevRoom->getH()) + prevRoom->getY();
					int y2;
					int x1;
					int x2 = (rand() % newRoom.getW()) + newRoom.getX();
					if (prevRoom->getX() > newRoom.getX())
					{
						x1 = prevRoom->getX();
					}
					else
					{
						x1 = prevRoom->getX() + prevRoom->getW() - 1;
					}
					if (prevRoom->getY() > newRoom.getY())
					{
						y2 = newRoom.getY() + newRoom.getH() - 1;
					}
					else
					{
						y2 = newRoom.getY();
					}

					addHCorridor(y1, x1, x2);
					addVCorridor(x2, y1, y2);
				}
				else
				{
					int x1 = (rand() % prevRoom->getW()) + prevRoom->getX();
					int y1;
					int x2;
					int y2 = (rand() % newRoom.getH()) + newRoom.getY();
					if (prevRoom->getX() > newRoom.getX())
					{
						x2 = newRoom.getX();
					}
					else
					{
						x2 = newRoom.getX() + newRoom.getW() - 1;
					}
					if (prevRoom->getY() > newRoom.getY())
					{
						y1 = prevRoom->getY() + prevRoom->getH() - 1;
					}
					else
					{
						y1 = prevRoom->getY();
					}

					addVCorridor(x1, y1, y2);
					addHCorridor(y2, x1, x2);
				}
			}
		}

	}

	// Place the stairs in a random room
	int randRoom = rand() % numRooms;
	int randRoomx = (rand() % (roomsVector[randRoom].getW()-2)) + roomsVector[randRoom].getX() + 1; // never next to walls
	int randRoomy = (rand() % (roomsVector[randRoom].getH()-2)) + roomsVector[randRoom].getY() + 1;
	tiles[randRoomx][randRoomy].setTileType(TILE_STAIRS);

	setTilesModels();

	// Add entities to the map
	randRoom = rand() % numRooms;
	randRoomx = (rand() % roomsVector[randRoom].getW()) + roomsVector[randRoom].getX();
	randRoomy = (rand() % roomsVector[randRoom].getH()) + roomsVector[randRoom].getY();
	player *newPlay = new player(randRoomx, randRoomy, "./asset/model/player_test.md2", this);
    entityList.push_back(newPlay);
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

void gamemap::addHCorridor(int y, int x1, int x2)
{
	if (x2 < x1) // just swap them
	{
		int temp = x1-1;
		x1 = x2;
		x2 = temp;
	}
	for (int i = x1; i <= x2; i++)
	{
		tiles[i][y].setTileType(TILE_FLOOR);
	}
}

void gamemap::addVCorridor(int x, int y1, int y2)
{
	if (y2 < y1) // just swap them
	{
		int temp = y1-1;
		y1 = y2;
		y2 = temp;
	}
	for (int i = y1; i <= y2; i++)
	{
		tiles[x][i].setTileType(TILE_FLOOR);
	}
}

bool gamemap::tileIsType(tile_types tileType, int x, int y)
{
	return tiles[x][y].getTileType() == tileType;
}

bool gamemap::dirIsType(directions direction, tile_types tileType, int x, int y)
{
	switch (direction)
	{
		case DIR_NORTH:
			return tileIsType(tileType, x, y-1);
		case DIR_EAST:
			return tileIsType(tileType, x+1, y);
		case DIR_SOUTH:
			return tileIsType(tileType, x, y+1);
		case DIR_WEST:
			return tileIsType(tileType, x-1, y);
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
					tiles[x][y].setRotation(90.0f);
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
			std::string texname = "./asset/texture/player_test.png";
			if (tiles[x][y].getTileType() == TILE_FLOOR)
				texname = "./asset/texture/tile_test.png";
			tiles[x][y].getTileModel()->renderFrame(0, position, tiles[x][y].getRotation(), texname);
		}
	}

	for (std::list<entity*>::iterator entityList_iter = entityList.begin(); entityList_iter != entityList.end(); entityList_iter++)
	{
		((*entityList_iter))->renderEntity();
	}
}

void gamemap::updateEntities(controls gameControls)
{
	for (std::list<entity*>::iterator entityList_iter = entityList.begin(); entityList_iter != entityList.end(); entityList_iter++)
	{
		(*entityList_iter)->update(this, gameControls);
	}
}

gamemap::~gamemap()
{
	for (std::list<entity*>::iterator entityList_iter = entityList.begin(); entityList_iter != entityList.end(); entityList_iter++)
	{
		// loop through the list
		delete *(entityList_iter); // delete the object
	}
}
