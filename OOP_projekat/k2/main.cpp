#include <iostream>
#include "Command.h"
#include "Parser.h"
#include "Program.h"
#include "Exceptions.h"
#include "NullArgumentCmd.h"
#include "Echo.h"
#include "Wc.h"
#include "Touch.h"


int main() {

	Stream* reader = new ConsoleStream();
	Parser* parser = new Parser();


	while (true) {
		try {
			cout << "$";
			string line = reader->getLine();
			if (line.length() > 512)
				line = line.substr(0, 512);

			if (reader->isEof())
				break;
			Command* cmd = parser->parseCommand(line);
			cmd->execute();

			delete cmd;
		}
		catch(Exception* e){
			cout << e->getMessage() << endl;
		}
	}

	


	return 0;
}