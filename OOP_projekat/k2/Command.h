#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include "Stream.h"
#include "Exceptions.h"

using namespace std;

class Command {
public:	
	virtual void execute() = 0;

	virtual ~Command(){}
private:
	virtual std::string getName() = 0;

};