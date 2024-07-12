#pragma once
#include "Structure.h"

class City : public Structure
{
public:
	static const int& length();
	int peopleCount;

	City() :Structure(1000), peopleCount(0) {}

	string getEntity() override;
	void addPeople(int count);
};
