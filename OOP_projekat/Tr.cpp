#include "Tr.h"

Tr::Tr(Stream* stream, string what)
	:OptionalArgumentCmd(stream),
	what(what)
{ }

Tr::Tr(Stream* stream, string what, string with)
	:OptionalArgumentCmd(stream),
	what(what), with(with)
{ }

void Tr::execute() {

    istream* input = this->stream->getInputStream();
    ostream* output = this->stream->getOutputStream();

    char c;
    string buffer;
    while (input->get(c)) {
        buffer += c;
    }
    cin.clear(); // ocisti buffer zbog EOF

    size_t pos = 0;
    while ((pos = buffer.find(what, pos)) != string::npos) {
        buffer.replace(pos, what.length(), with);
        pos += with.length();
    }

    *output << buffer;
}

//istream* input = this->stream->getInputStream();
//ostream* output = this->stream->getOutputStream();

//string line;
//size_t pos = 0;   // ????
//while (getline(*input, line)) {
//	pos = 0;
//	while (line.find(what, pos) != string::npos) {

//		pos = line.find(what);
//		line.replace(pos, what.length(), with);
//		pos += with.length();
//	}

//	*output << line << endl;
//}
