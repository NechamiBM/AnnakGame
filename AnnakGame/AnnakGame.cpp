#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Input.h"
#include "Utility.h"
#include "Configuration.h"
#include "Tile.h"
#include "World.h"
#include "Actions.h"
using namespace std;

void startState(World& world, vector<shared_ptr<Command>> commands) {
	for (const auto& command : commands)
		if (command->name == Command::RESOURCE)
			Actions::resource(world, command);
		else if (command->name == Command::PEOPLE)
			Actions::people(world, command);
		else if (command->name == Command::BUILD)
			Actions::build(world, command, true);
}

void step(World& world, shared_ptr<Command> command) {
	if (command->name == Command::SELECT)
		Actions::select(world, command);
	else if (command->name == Command::WORK)
		Actions::work(world, command);
	else if (command->name == Command::WAIT)
		Actions::wait(world, stoi(command->arguments[0]));
	else if (command->name == Command::RAIN)
		Actions::rain(world, command);
	else if (command->name == Command::BUILD)
		Actions::build(world, command, false);
	else if (command->name == Command::PEOPLE)
		Actions::people(world, command);
}

string assert(World& world, string assertCommand) {
	stringstream output;

	output << assertCommand << ' ';
	if (assertCommand == "SelectedCategory") {
		string selectedCategory = world.grid[world.yLocation][world.xLocation].getCategory()->getEntity();
		output << selectedCategory;
	}
	else if (assertCommand == "SelectedResource") {
		vector<int> resourceCounts(Configuration::resourceTypes().size() - 1, 0); //Not Include People

		string category = world.grid[world.yLocation][world.xLocation].tile->getCategoryString();
		string resourse = Configuration::categoryToResource().at(category);

		auto it = find(Configuration::resourceTypes().begin(), Configuration::resourceTypes().end(), resourse);
		int index = distance(Configuration::resourceTypes().begin(), it);
		resourceCounts[index] = world.grid[world.yLocation][world.xLocation].tile->getResourceCount();
		for (auto& res : resourceCounts)
			output << ' ' << res;
	}
	else if (assertCommand == "SelectedPeople") {
		output << world.grid[world.yLocation][world.xLocation].getPeopleCount();
	}
	else if (assertCommand == "SelectedComplete") {
		output << boolalpha << world.grid[world.yLocation][world.xLocation].structure->isComplete();
	}
	else if (assertCommand == "CityCount") {
		output << world.citiesCount();
	}
	else if (assertCommand == "VillageCount") {
		output << world.villagesCount();
	}
	else if (assertCommand == "RoadCount") {
		output << world.roadsCount();
	}

	return output.str();
}

void simulateGame(Input& input) {
	input.parse_and_store();

	World world(input.world->data);


	startState(world, input.start);

	for (const auto& command : input.steps)
		step(world, command);

	stringstream output;
	for (const auto& assertCommand : input.asserts)
		output << assert(world, assertCommand) << endl;

	cout << output.str();
}

int main() {
	try {
		string s;
		getline(cin, s);
		Configuration::loadConfiguration("configuration.json");
		Input input("", "");
		simulateGame(input);
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
	return 0;
}