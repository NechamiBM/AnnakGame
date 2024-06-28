#pragma once
#include <vector>
#include <string>
#include "Configuration.h"
using namespace std;

class Tile
{
	int category;
	string categoryString;
	int resourceCount;
	int peopleCount = 0;
	vector<vector<int>> grid;
public:
	static const int& length();
	Tile(int category);
	string& getCategoryString() { return categoryString; }
	int& getResourceCount() { return resourceCount; }
	int& getPeopleCount() { return peopleCount; }
	vector<vector<int>>& getGrid() { return grid; }
	void setResourceCount(int cnt) { resourceCount = cnt; }
	void addPeople(int cnt) { peopleCount += cnt; }
};

