#include "Village.h"
#include "Configuration.h"

const int& Village::length(){
	static int _length = Configuration::sizes().at("Village").first;
	return _length;
}

string Village::getEntity(){
	return "Village";
}

void Village::addPeople(int count){
	peopleCount += count;
	int maxPoeopleCount = Configuration::capacities().at("Village")[4];
	if (peopleCount > maxPoeopleCount)
		peopleCount = maxPoeopleCount;
}
