#include "Head.h"


Head::Head(Stream* stream, int count)
	: OptionalArgumentCmd(stream),
	count(count)
{ }

void Head::execute(){

	istream* input = this->stream->getInputStream();
	ostream* output = this->stream->getOutputStream();

	if (input == &cin) Stream::noArgumentStream(input); //nije potrebno, samo radi postizanja efekta buffer citanja

    int i = 0;
    string line;
    while (i < count && getline(*input, line)) {
        *output << line;
        if (!input->eof())
            *output << endl;
        i++;
    }
}
