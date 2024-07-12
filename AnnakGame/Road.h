#pragma once
#include "Structure.h"
class Road : public Structure
{
public:
	static const int& length();

	string getEntity() override;
	Road() :Structure(200) {	}
};

