#include "Pipeline.h"

Pipeline::Pipeline(vector<Command*> commands)
	: commands(commands)
{ }

Pipeline::~Pipeline()
{
	for (auto cmd : commands)
		delete cmd;
}

void Pipeline::execute(){
	int n = commands.size();

	vector<stringstream*> buffers;
	for (int i = 0; i < n - 1; i++)
		buffers.push_back(new stringstream());

	Command* cmd;
	for (int i = 0; i < n; i++) {

		cmd = commands[i];
		Stream* stream = cmd->getStream();

		if (i > 0) {
			stream->setInputStream(buffers[i - 1]);
		}
		if (i < n - 1) {
			stream->setOutputStream(buffers[i]);
		}
		
		cmd->execute();

		//odvoji buffer od komande 
		stream->setInputStream(&cin);
		stream->setOutputStream(&cout);
	}

	for (stringstream* buf : buffers)
		delete buf;
}
