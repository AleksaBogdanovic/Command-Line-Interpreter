#include "Batch.h"

Batch::Batch(string argument, Parser* p)
	:	ArgumentCmd(argument)
	,	parser(p)
	,	outFilename("")
{ }

Batch::Batch(string argument, string outFilename, Parser * p)
	:	ArgumentCmd(argument)
	,	parser(p)
	,	outFilename(outFilename)
{ }

void Batch::execute() {

	ostream* oldOutput = parser->getDefaultOutput();
	
	if (!fileExists()) Exception::fileNotExists(this->getName(), argument);
	ifstream file(argument);

	std::ofstream outFile;

	if (!outFilename.empty()) {
		outFile.open(outFilename);
		if (!outFile)
			Exception::cannotCreateFile(this->getName(), outFilename);

		parser->setDefaultOutput(&outFile);
	}

	string line;
	ostream* output = parser->getDefaultOutput();
	while (getline(file, line)) {
		try {
			
			if (line.length() > 512)
				line = line.substr(0, 512);

			Command* cmd = parser->parseCommand(line);
			cmd->execute();
			*output << endl;

			delete cmd;
		}
		catch (Exception* e) {
			cout << e->getMessage() << endl;
		}
	}

	parser->setDefaultOutput(oldOutput);

}