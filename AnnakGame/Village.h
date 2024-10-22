#pragma once
#include "Structure.h"

class Village :public Structure
{
public:
	static const int& length();
	int peopleCount;

	Village() :Structure(1000), peopleCount(0) {}

	string getEntity() override;

	void addPeople(int count);
};