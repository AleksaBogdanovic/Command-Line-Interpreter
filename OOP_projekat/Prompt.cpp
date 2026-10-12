#include "Prompt.h"

string Prompt::prompt = "$";

void Prompt::execute(){
	prompt = argument;
}

void Prompt::print(){
	cout << prompt;
}
