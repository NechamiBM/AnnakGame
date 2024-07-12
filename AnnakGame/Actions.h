#pragma once
#include "World.h"
#include "Command.h"
#include "Road.h"

class Actions
{
public:
	static void resource(World& world, shared_ptr<Command> command);
	static void people(World& world, shared_ptr<Command> command);


	static void select(World& world, shared_ptr<Command> command);
	static void work(World& world, shared_ptr<Command> command);
	static void wait(World& world, int waitTime);
	static void rain(World& world, shared_ptr<Command> command);
	static void build(World& world, shared_ptr<Command> command, bool isStart);
};

