#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Input.h"
#include "Utility.h"
#include "Configuration.h"
#include "Tile.h"
#include "World.h"
using namespace std;

void simulateGame(Input& input) {
	input.parse_and_store();

	World world(input.world->data);

	stringstream output;
	for (const auto& command : input.start) {
		if (command->name == Command::RESOURCE) {
			int resourceCount = stoi(command->arguments[0]);
			world.xLocation = stoi(command->arguments[2]);
			world.yLocation = stoi(command->arguments[3]);
			world.worldMap[world.yLocation][world.xLocation].tile->setResourceCount(resourceCount);
		}
		else if (command->name == Command::PEOPLE) {
			int peopleCount = stoi(command->arguments[0]);
			world.xLocation = stoi(command->arguments[1]);
			world.yLocation = stoi(command->arguments[2]);
			world.worldMap[world.yLocation][world.xLocation].tile->addPeople(peopleCount);
		}
	}

	for (const auto& command : input.steps)
		if (command->name == Command::SELECT) {
			world.xLocation = (stoi(command->arguments[0]) - 1);
			world.yLocation = (stoi(command->arguments[1]) - 1);

			if (world.xLocation < 0 || world.xLocation >= world.worldMap[0].size() || world.yLocation < 0 || world.yLocation >= world.worldMap.size())
				throw runtime_error("Coordinates out of range.");
		}

	for (const auto& assertCommand : input.asserts) {
		output << assertCommand;
		if (assertCommand == "SelectedCategory") {
			string selectedCategory = world.worldMap[world.yLocation][world.xLocation].tile->getCategoryString();
			output << ' ' << selectedCategory << endl;
		}
		else if (assertCommand == "SelectedResource") {
			vector<int> resourceCounts(Configuration::resourceTypes().size() - 1, 0); //Not Include People

			string category = world.worldMap[world.yLocation][world.xLocation].tile->getCategoryString();
			string resourse = Configuration::categoryToResource().at(category);

			auto it = find(Configuration::resourceTypes().begin(), Configuration::resourceTypes().end(), resourse);
			int index = distance(Configuration::resourceTypes().begin(), it);
			resourceCounts[index] = world.worldMap[world.yLocation][world.xLocation].tile->getResourceCount();
			for (auto& res : resourceCounts)
				output << ' ' << res;
		}
	}
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