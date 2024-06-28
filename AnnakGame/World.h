#pragma once
#include <vector>
#include "Cell.h"
using namespace std;

class World
{
public:
	int xLocation, yLocation;
	vector<vector<Cell>> worldMap;
	World(vector<vector<string>>& data);
	void initWorld(vector<vector<string>>& data);
};
