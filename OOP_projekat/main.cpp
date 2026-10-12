#include <iostream>
#include "Command.h"
#include "Parser.h"
#include "Program.h"
#include "Exceptions.h"
#include "NullArgumentCmd.h"
#include "Prompt.h"


int main() {

	Stream* reader = new ConsoleStream();
	Parser* parser = new Parser();
	Prompt* prompt = new Prompt();


	while (true) {
		try {
			prompt->print();
			string line = reader->getLine();
			if (line.length() > 512)
				line = line.substr(0, 512);

			if (reader->isEof())
				break;
			Command* cmd = parser->parseCommand(line);
			cmd->execute();

			cout << endl;

			delete cmd;
		}
		catch(Exception* e){
			cout << e->getMessage() << endl;
		}
	}

	


	return 0;
}