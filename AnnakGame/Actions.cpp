#include "Actions.h"
#include <algorithm> 

void Actions::resource(World& world, shared_ptr<Command> command) {
	int resourceCount = stoi(command->arguments[0]);
	world.xLocation = stoi(command->arguments[2]);
	world.yLocation = stoi(command->arguments[3]);
	world.grid[world.yLocation][world.xLocation].tile->setResourceCount(resourceCount);
}

void Actions::people(World& world, shared_ptr<Command> command) {
	int peopleCount = stoi(command->arguments[0]);
	world.xLocation = stoi(command->arguments[1]) - 1;
	world.yLocation = stoi(command->arguments[2]) - 1;
	world.grid[world.yLocation][world.xLocation].addPeople(peopleCount);
}

void Actions::select(World& world, shared_ptr<Command> command) {
	world.xLocation = stoi(command->arguments[0]) - 1;
	world.yLocation = stoi(command->arguments[1]) - 1;

	if (world.xLocation < 0 || world.xLocation >= world.grid[0].size() ||
		world.yLocation < 0 || world.yLocation >= world.grid.size())
		throw runtime_error("Coordinates out of range.");
}

void Actions::work(World& world, shared_ptr<Command> command) {
	world.grid[world.yLocation][world.xLocation].addPeople(-1);
	world.xLocation = stoi(command->arguments[0]) - 1;
	world.yLocation = stoi(command->arguments[1]) - 1;
	world.grid[world.yLocation][world.xLocation].addPeople(1);
}

void Actions::wait(World& world, int waitTime) {
	world.rainCount -= waitTime;
	for (auto& entry : world.activityTime)
		entry.second += waitTime;

	if (world.activityTime[Command::WORK] >= 1000) {
		world.grid[world.yLocation][world.xLocation].tile->setResourceCount(0);
		world.activityTime[Command::WORK] = 0;
	}
	if (world.rainCount < 0) {
		world.activityTime["Wood"] += world.rainCount;
		world.activityTime["Wool"] += world.rainCount;
	}
	for (auto& entry : Configuration::rains()) {
		if (world.activityTime[entry.first] >= entry.second) {
			world.activityTime[entry.first] -= entry.second;
			for (int i = 0; i < world.grid.size(); i += Tile::length())
				for (int j = 0; j < world.grid[0].size(); j += Tile::length()) {
					bool isForestWood = world.grid[j][i].tile->getCategoryString() == "Forest" && entry.first == "Wood";
					bool isFieldWool = world.grid[j][i].tile->getCategoryString() == "Field" && entry.first == "Wool";

					if (isForestWood || isFieldWool) {
						int count = world.grid[j][i].tile->getResourceCount();
						world.grid[j][i].tile->setResourceCount(count + 1);
					}
				}
		}
	}
	for (auto& city : world.cities) {
		if (city && city->completeTime > 0)
			city->completeTime -= waitTime;
	}
}

void Actions::rain(World& world, shared_ptr<Command> command) {
	world.rainCount = stoi(command->arguments[0]);
}

bool isConnected(World& world, int x, int y, int length, const string& type) {
	// Check all cells around the new structure
	for (int i = -1; i <= length; i++) {
		for (int j = -1; j <= length; j++) {
			if ((i == -1 || i == length) || (j == -1 || j == length)) {
				int newY = y + i;
				int newX = x + j;
				if (newY >= 0 && newY < world.grid.size() && newX >= 0 && newX < world.grid[newY].size())
					if (((type == "City" || type == "Village") && dynamic_cast<Road*>(world.grid[newY][newX].structure.get()) != nullptr)
						|| (type == "Road" && world.grid[newY][newX].structure != nullptr))
						return true;
			}
		}
	}
	return false;
}

void Actions::build(World& world, shared_ptr<Command> command, bool isStart) {
	world.xLocation = stoi(command->arguments[1]) - 1;
	world.yLocation = stoi(command->arguments[2]) - 1;
	shared_ptr<Structure> structure;
	int length = 0;

	if (command->arguments[0] == "City") {
		if (!isStart && !isConnected(world, world.xLocation, world.yLocation, City::length(), "City"))
			return;

		structure = world.addCity();
		length = City::length();
	}
	else if (command->arguments[0] == "Village") {
		if (!isStart && !isConnected(world, world.xLocation, world.yLocation, Village::length(), "Village"))
			return;

		structure = world.addVillage();
		length = Village::length();
	}
	else if (command->arguments[0] == "Road") {
		if (!isStart && !isConnected(world, world.xLocation, world.yLocation, Road::length(), "Road"))
			return;

		structure = world.addRoad();
		length = Road::length();
	}

	for (int i = world.yLocation; i < world.yLocation + length; i++)
		for (int j = world.xLocation; j < world.xLocation + length; j++)
			world.grid[i][j].structure = structure;
}
