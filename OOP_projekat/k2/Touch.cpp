#include "Touch.h"



void Touch::execute()
{
	if (fileExists()) Exception::fileAlreadyExists(this->getName(), argument);

	std::ofstream newFile(argument);

	if (!newFile) Exception::cannotCreateFile(this->getName(), argument);
}
