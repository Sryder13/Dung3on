#include "gamemap.hpp"

void tile::setTileModel(const std::string &filename)
{
	model = resourcemanager::getResourceManager()->getResource<md2>(filename);
}

void gamemap::generateMap()
{
    for (int x = 0; x < MAP_X_SIZE; x++)
    {
		for (int y = 0; y < MAP_Y_SIZE; y++)
		{
			tiles[x][y].setTileType(TILE_FLOOR);
		}
    }
    setTilesModels();
}

int gamemap::surroundingWallsNum(int x, int y)
{
	int numSurroundingWalls = 0;
	if (x < 0 || x >= MAP_X_SIZE)
	{
		std::cout << "gamemap::surroundingWallsNum: invalid map x position: " << x << std::endl;
		return 0;
	}

	if (y < 0 || y >= MAP_X_SIZE)
	{
		std::cout << "gamemap::surroundingWallsNum: invalid map y position: " << y << std::endl;
		return 0;
	}

	if (x == 0 || x == MAP_X_SIZE-1) // if it's on the edges it has a wall
		numSurroundingWalls++;
	if (y == 0 || y == MAP_Y_SIZE-1)
		numSurroundingWalls++;

	if (x > 0)
		if (tiles[x-1][y].getTileType() == TILE_WALL)
			numSurroundingWalls++;
	if (x < MAP_X_SIZE-1)
		if (tiles[x+1][y].getTileType() == TILE_WALL)
			numSurroundingWalls++;
	if (y > 0)
		if (tiles[x][y-1].getTileType() == TILE_WALL)
			numSurroundingWalls++;
	if (x < MAP_Y_SIZE-1)
		if (tiles[x][y+1].getTileType() == TILE_WALL)
			numSurroundingWalls++;

	if (numSurroundingWalls > 4)
	{
		std::cout << "Too many surrounding walls on tile " << x << "," << y <<std::endl;
		numSurroundingWalls = 4;
	}

	return numSurroundingWalls;

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
				{
					int numSurroundingWalls = surroundingWallsNum(x, y);
					// TODO (sean): determine tile rotation based on where walls are

					if (numSurroundingWalls == 0)
						modelFile = "./asset/model/tile_1.md2"; // TODO (sean): A no walls floor model
					else if (numSurroundingWalls == 1)
						modelFile = "./asset/model/tile_1.md2";
					else if (numSurroundingWalls == 2)
						modelFile = "./asset/model/tile_2.md2"; // TODO (sean): Fix this, there needs to be a corner walls version
					else if (numSurroundingWalls == 3)
						modelFile = "./asset/model/tile_3.md2";
					else if (numSurroundingWalls == 4)
						modelFile = "./asset/model/tile_4.md2";
				}
					break;
				case TILE_WALL:
					// TODO (sean): An actual wall model
					modelFile = "./asset/model/sphere_test.md2";
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
			vec3 pos = {x, 0.0f, y};
			tiles[x][y].getTileModel()->renderFrame(0, pos);
		}
	}
}
