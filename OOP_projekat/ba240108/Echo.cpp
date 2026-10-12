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

	if (input == &cin) Stream::noArgumentStream(input); //nije potrebno, samo radi postizanja efekta buffer citanja
	
	/*string result;
	while (getline(*input, result)) {
		*output << result << endl;
	}*/

	char c;
	while (input->get(c)) {
		*output << c;
	}
	output->flush();
}
