#include "Road.h"
#include "Configuration.h"

const int& Road::length() {
	static int _length = Configuration::sizes().at("Road").first;
	return _length;
}

string Road::getEntity() {
	return "Road";
}

