#pragma once

#include <list>
#include "Command.h"

//Singleton DP
class Program {

public:

	static Program* Instance();

	void add(Command* cmd);
	void executeNext();
	bool hasNext();


private:
	Program();

	static Program* s_instance;

	std::list<Command*> commands;
	list<Command*>::iterator it;
};
