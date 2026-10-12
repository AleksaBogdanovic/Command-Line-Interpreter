#include "Truncate.h"

void Truncate::execute()
{

	if (!fileExists()) Exception::fileNotExists(this->getName(), argument);

	std::ofstream deletedFile(argument);

}