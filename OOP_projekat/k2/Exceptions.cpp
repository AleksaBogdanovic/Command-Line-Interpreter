#include "Exceptions.h"

Exception::Exception(string message)
	:	message(message)
{ }

void Exception::fileAlreadyExists(const string& name, const string& filename){
	string message = name + ": '" + filename + "' file already exists";
	throw new Exception(message);
}

void Exception::cannotCreateFile(const string& name, const string& filename){
	string message = name + ": '" + filename + "' cannot create specified file";
	throw new Exception(message);
}

void Exception::unableToOpenFile(const string& name, const string& filename){
	string message = name + ": '" + filename + "' unable to open file";
	throw new Exception(message);
}
