#include "Actions.h"

void Actions::resource(World& world, shared_ptr<Command> command) {
	int resourceCount = stoi(command->arguments[0]);
	world.xLocation = stoi(command->arguments[2]);
	world.yLocation = stoi(command->arguments[3]);
	world.worldMap[world.yLocation][world.xLocation].tile->setResourceCount(resourceCount);
}

void Actions::people(World& world, shared_ptr<Command> command) {
	int peopleCount = stoi(command->arguments[0]);
	world.xLocation = stoi(command->arguments[1]) - 1;
	world.yLocation = stoi(command->arguments[2]) - 1;
	world.worldMap[world.yLocation][world.xLocation].tile->addPeople(peopleCount);
}

void Actions::select(World& world, shared_ptr<Command> command) {
	world.xLocation = stoi(command->arguments[0]) - 1;
	world.yLocation = stoi(command->arguments[1]) - 1;

	if (world.xLocation < 0 || world.xLocation >= world.worldMap[0].size() ||
		world.yLocation < 0 || world.yLocation >= world.worldMap.size())
		throw runtime_error("Coordinates out of range.");
}

void Actions::work(World& world, shared_ptr<Command> command) {
	world.worldMap[world.yLocation][world.xLocation].people = false;
	world.xLocation = stoi(command->arguments[0]) - 1;
	world.yLocation = stoi(command->arguments[1]) - 1;
	world.worldMap[world.yLocation][world.xLocation].people = true;
}

void Actions::wait(World& world, shared_ptr<Command> command) {
	int waitTime = stoi(command->arguments[0]);
	world.rainCount -= waitTime;
	for (auto& entry : world.activityTime)
		entry.second += waitTime;

	if (world.activityTime[Command::WORK] >= 1000) {
		world.worldMap[world.yLocation][world.xLocation].tile->setResourceCount(0);
		world.activityTime[Command::WORK] = 0;
	}
	if (world.rainCount < 0) {
		world.activityTime["Wood"] += world.rainCount;
		world.activityTime["Wool"] += world.rainCount;
	}
	for (auto& entry : Configuration::rains()) {
		if (world.activityTime[entry.first] >= entry.second) {
			world.activityTime[entry.first] -= entry.second;
			for (int i = 0; i < world.worldMap.size(); i += Tile::length())
				for (int j = 0; j < world.worldMap[0].size(); j += Tile::length()) {
					bool isForestWood = world.worldMap[j][i].tile->getCategoryString() == "Forest" && entry.first == "Wood";
					bool isFieldWool = world.worldMap[j][i].tile->getCategoryString() == "Field" && entry.first == "Wool";

					if (isForestWood || isFieldWool) {
						int count = world.worldMap[j][i].tile->getResourceCount();
						world.worldMap[j][i].tile->setResourceCount(count + 1);
					}
				}
		}
	}
}

void Actions::rain(World& world, shared_ptr<Command> command) {
	world.rainCount = stoi(command->arguments[0]);
}

