#pragma once
#include "Entity.h"

class Structure : public Entity
{
public:
	int completeTime;

	Structure(int time):completeTime(time){}
	bool isComplete();
};
