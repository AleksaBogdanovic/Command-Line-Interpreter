#include "OptionalArgumentCmd.h"

OptionalArgumentCmd::OptionalArgumentCmd(const string& argument)
{
	//stream = Stream::createStream(argument);
}

OptionalArgumentCmd::OptionalArgumentCmd(Stream* stream)
	:	stream(stream)
{ }

OptionalArgumentCmd::~OptionalArgumentCmd(){
	delete stream;
}
