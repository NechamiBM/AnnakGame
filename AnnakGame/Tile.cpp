#include "Tile.h"
#include <iostream>

const int& Tile::length() {
	static int _length = Configuration::sizes().at("Tile").first;
	return _length;
}

Tile::Tile(int category) :category(category), resourceCount(0) {
	int len = length();
	grid.resize(len, vector<int>(len, category));
	categoryString = Configuration::tileCategories().at(category);

	auto it = Configuration::startingResources().find(categoryString);
	if (it != Configuration::startingResources().end())
		resourceCount = it->second;
}
