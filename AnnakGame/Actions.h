#pragma once
#include "World.h"
#include "Command.h"

class Actions
{
public:
	static void resource(World& world, shared_ptr<Command> command);
	static void people(World& world, shared_ptr<Command> command);


	static void select(World& world, shared_ptr<Command> command);
};

