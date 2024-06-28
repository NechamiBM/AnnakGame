#include "Actions.h"

void Actions::resource(World& world, shared_ptr<Command> command) {
	int resourceCount = stoi(command->arguments[0]);
	world.xLocation = stoi(command->arguments[2]);
	world.yLocation = stoi(command->arguments[3]);
	world.worldMap[world.yLocation][world.xLocation].tile->setResourceCount(resourceCount);
}

void Actions::people(World& world, shared_ptr<Command> command){
	int peopleCount = stoi(command->arguments[0]);
	world.xLocation = stoi(command->arguments[1]);
	world.yLocation = stoi(command->arguments[2]);
	world.worldMap[world.yLocation][world.xLocation].tile->addPeople(peopleCount);
}

void Actions::select(World& world, shared_ptr<Command> command){
	world.xLocation = (stoi(command->arguments[0]) - 1);
	world.yLocation = (stoi(command->arguments[1]) - 1);

	if (world.xLocation < 0 || world.xLocation >= world.worldMap[0].size() ||
		world.yLocation < 0 || world.yLocation >= world.worldMap.size())
		throw runtime_error("Coordinates out of range.");
}

