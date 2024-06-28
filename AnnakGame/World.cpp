#include "World.h"

World::World(vector<vector<string>>& data){
	initWorld(data);
	xLocation = yLocation = 0;
}

void World::initWorld(vector<vector<string>>& categories)
{
	int rows = categories.size();
	int cols = categories[0].size();
	worldMap.resize(rows * Tile::length(), vector<Cell>(cols * Tile::length()));

	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j) {
			int category = stoi(categories[i][j]);
			auto tile = make_shared<Tile>(category);

			for (int x = i * Tile::length(); x < (i + 1) * Tile::length(); ++x)
				for (int y = j * Tile::length(); y < (j + 1) * Tile::length(); ++y)
					worldMap[x][y].tile = tile;
		}
}
