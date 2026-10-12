#include "Rm.h"
#include <cstdio>

void Rm::execute()
{

	if (!fileExists()) Exception::fileNotExists(this->getName(), argument);

	remove(argument.c_str());

	if (fileExists()) Exception::unableToDeleteFile(this->getName(), argument);

}