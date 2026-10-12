#include "Echo.h"


Echo::Echo(const string& argument)
	:	OptionalArgumentCmd(argument)
{ }

Echo::Echo(Stream * stream)
	:	OptionalArgumentCmd(stream)
{ }

void Echo::execute()
{
	istream* input = this->stream->getInputStream();
	ostream* output = this->stream->getOutputStream();
	
	string result;
	while (getline(*input, result)) {
		*output << result << endl;
	}
}
