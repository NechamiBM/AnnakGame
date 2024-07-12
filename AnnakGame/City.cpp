#include "City.h"
#include "Configuration.h"

const int& City::length() {
	static int _length = Configuration::sizes().at("City").first;
	return _length;
}

string City::getEntity() {
	return "City";
}

void City::addPeople(int count) {
	peopleCount += count;
	int maxPoeopleCount = Configuration::capacities().at("City")[4]; 
	if (peopleCount > maxPoeopleCount)
		peopleCount = maxPoeopleCount;
}
