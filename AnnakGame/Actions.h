#pragma once
#include "World.h"
#include "Command.h"

class Actions
{
public:
	static void resource(World& world, shared_ptr<Command> command);
	static void people(World& world, shared_ptr<Command> command);


	static void select(World& world, shared_ptr<Command> command);
	static void work(World& world, shared_ptr<Command> command);
	static void wait(World& world, shared_ptr<Command> command);
	static void rain(World& world, shared_ptr<Command> command);
};

