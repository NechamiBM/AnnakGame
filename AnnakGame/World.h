#pragma once
#include <vector>
#include "Cell.h"
#include "City.h"
using namespace std;

class World
{
public:
	int xLocation, yLocation;
	map<string, int> activityTime = { {"Wood", 0}, {"Wool", 0}, {"Work", 0} };
	int rainCount = 0;
	vector<vector<Cell>> grid;
	vector<shared_ptr<City>> cities;
	vector<shared_ptr<Village>> villages;
	vector<shared_ptr<Road>> roads;

	World(vector<vector<string>>& data);
	void initWorld(vector<vector<string>>& data);
	shared_ptr<City> addCity();
	shared_ptr<Village> addVillage();
	shared_ptr<Road> addRoad();
	int citiesCount();
	int villagesCount();
	int roadsCount();
};
