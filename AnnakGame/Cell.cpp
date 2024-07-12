#include "Cell.h"

shared_ptr<Entity> Cell::getCategory() {
	/* if (peopleCount > 0)
		 return people;*/
	if (structure)
		return structure;
	else
		return tile;

}

int Cell::getPeopleCount() {
	City* city = dynamic_cast<City*>(structure.get());
	Village* village = dynamic_cast<Village*>(structure.get());

	if (city != nullptr)
		return city->peopleCount;
	if (village != nullptr)
		return village->peopleCount;
	return peopleCount;
}

void Cell::addPeople(int count) {
	City* city = dynamic_cast<City*>(structure.get());
	Village* village = dynamic_cast<Village*>(structure.get());

	if (city != nullptr)
		city->addPeople(count);
	else if (village != nullptr)
		village->addPeople(count);
	else {
		peopleCount += count;
		if (count < 0)
			peopleCount = 0;
		else if (count > 1)
			peopleCount = 1;
	}
}
