#include "World.h"

World::World(vector<vector<string>>& data){
	initWorld(data);
	xLocation = yLocation = 0;
}

void World::initWorld(vector<vector<string>>& categories){
	int rows = categories.size();
	int cols = categories[0].size();
	grid.resize(rows * Tile::length(), vector<Cell>(cols * Tile::length()));

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			int category = stoi(categories[i][j]);
			auto tile = make_shared<Tile>(category);

			for (int x = i * Tile::length(); x < (i + 1) * Tile::length(); ++x)
				for (int y = j * Tile::length(); y < (j + 1) * Tile::length(); ++y)
					grid[x][y].tile = tile;
		}
	}
}

shared_ptr<City> World::addCity(){
	shared_ptr<City> cityToAdd= make_shared<City>();
	cities.emplace_back(cityToAdd);
	return cityToAdd;
}

shared_ptr<Village> World::addVillage(){
	shared_ptr<Village> villageToAdd = make_shared<Village>();
	villages.emplace_back(villageToAdd);
	return villageToAdd;
}

shared_ptr<Road> World::addRoad(){
	shared_ptr<Road> roadToAdd = make_shared<Road>();
	roads.emplace_back(roadToAdd);
	return roadToAdd;
}

int World::citiesCount(){
	return int(cities.size());
}

int World::villagesCount(){
	return int(villages.size());
}

int World::roadsCount(){
	return int(roads.size());
}
