#include "Wc.h"


Wc::Wc(Stream* stream)
	: OptionalArgumentCmd(stream)
{ }

WcWord::WcWord(Stream* stream)
	: Wc(stream)
{ }

WcCharacter::WcCharacter(Stream* stream)
	: Wc(stream)
{ }

void Wc::execute()
{
	istream* input = stream->getInputStream();
	ostream* output = stream->getOutputStream();

	int result = this->count(input);
	
	*output << result << endl;
}

int WcCharacter::count(istream* input)
{
	int cnt = 0;
	char c;
	while (input->get(c)) {
		cnt++;
	}
	return cnt;
}

int WcWord::count(istream* input)
{
	int cnt = 0;
	string accept;
	while (*input >> accept)
		cnt++;

	return cnt;
}
