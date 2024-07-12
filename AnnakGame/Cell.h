#pragma once
#include <memory>
#include <iostream>
#include "Tile.h"
#include "Road.h"
#include "City.h"
#include "Village.h"
#include "Structure.h"
using namespace std;

class Cell
{
private:
	int peopleCount;

public:
	shared_ptr<Tile> tile;
	shared_ptr<Structure> structure;

	Cell() :tile(nullptr), peopleCount(0) { }
	shared_ptr<Entity> getCategory();
	int getPeopleCount();
	void addPeople(int count);
};

