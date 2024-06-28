#pragma once
#include <memory>
#include <iostream>
#include "Tile.h"
#include "Village.h"
using namespace std;

class Cell
{
public:
	shared_ptr<Tile> tile;
	shared_ptr<Village> village;
	bool people;
	Cell() :tile(nullptr), village(nullptr), people(false){	}
};

