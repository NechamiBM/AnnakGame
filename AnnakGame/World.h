#pragma once
#include <vector>
#include "Cell.h"
using namespace std;

class World
{
public:
	int xLocation, yLocation;
	map<string, int> activityTime = { {"Wood", 0}, {"Wool", 0}, {"Work", 0} };
	int rainCount = 0;
	vector<vector<Cell>> worldMap;
	World(vector<vector<string>>& data);
	void initWorld(vector<vector<string>>& data);
};
