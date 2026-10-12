#pragma once

#include "Command.h" 

class ArgumentCmd : public Command {
public:
	ArgumentCmd(string argument);
	ArgumentCmd();

	virtual void execute() = 0;

protected:
	bool fileExists();

	string argument;
};


inline bool ArgumentCmd::fileExists() {

	return static_cast<bool>(ifstream(argument));
}