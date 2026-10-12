#include "Exceptions.h"
#include "Parser.h"

Exception::Exception(string message)
	:	message(message)
{ }

void Exception::fileAlreadyExists(const string& name, const string& filename){
	string message = name + ": '" + filename + "' file already exists";
	throw new Exception(message);
}

void Exception::fileNotExists(const string& name, const string& filename){
	string message = name + ": '" + filename + "' file does not exist";
	throw new Exception(message);
}

void Exception::cannotCreateFile(const string& name, const string& filename){
	string message = name + ": '" + filename + "' cannot create specified file";
	throw new Exception(message);
}

void Exception::unableToOpenFile(const string& name, const string& filename){
	string message = name + ": '" + filename + "' unable to open file";
	throw new Exception(message);
}

void Exception::unableToDeleteFile(const string& name, const string& filename){
	string message = name + ": '" + filename + "' unable to delete file";
	throw new Exception(message);
}


string Exception::syntaxErorrMessage(const string& line, int position){
	string message = '\n' + line + '\n';
	for (int i = 0; i < position; i++) message.push_back(' ');
	message.push_back('^');
	return message;
}

void Exception::unexpectedCharacter(const string& line, int position){
	string message = "Error: unexpected character" + Exception::syntaxErorrMessage(line, position);
	throw new Exception(message);
}

void Exception::missingCharacters(const string& line, int position){
	string message = "Error: characters missing" + Exception::syntaxErorrMessage(line, position);
	throw new Exception(message);
}

void Exception::missingClosedQuotation(const string& line, int position){
	string message = "Error: missing closed quotation mark" + Exception::syntaxErorrMessage(line, position);
	throw new Exception(message);
}

void Exception::unknownCommand(const string& name){
	string message = "Unknown command: " + name;
	throw new Exception(message);
}

void Exception::badTypeCommand(){
	string message = "Error: first word must begin with alphabetical character";
	throw new Exception(message);
}

void Exception::emptyCommand(){
	string message = "Error: cannot parse empty command nor '| |' in pipeline";
	throw new Exception(message);
}

void Exception::tooManyArguments(const string& name){
	string message = name + ": too many arguments for command to execute";
	throw new Exception(message);
}

void Exception::missingRedirectionArgument(const string& name, Token t){
	string message = name + ": ";

	switch (t.kind) {
	case TokenType::RedirectInput:
		message += "input redirection(<) ";
		break;
	case TokenType::RedirectOutput:
		message += "output redirection(>) ";
		break;
	case TokenType::DoubleRedirectOutput:
		message += "append output redirection(>>) ";
		break;
	}

	message += "is missing or has wrong type of argument";
	throw new Exception(message);

}

void Exception::onlyOutRedirectAllowed(const string& name){
	string message = name + ": only output redirection is allowed";
	throw new Exception(message);
}

void Exception::optionExpected(const string& name, int i){
	string message = name + ": option expected as argument number " + to_string(i);
	throw new Exception(message);
}

void Exception::invalidOption(const string& name, const string& expected){
	string message = name + ": invalid option, expected one of: " +  expected;
	throw new Exception(message);
}

void Exception::multipleInputSources(const string& name){
	string message = name + ": ambiguous input stream sources";
	throw new Exception(message);
}

void Exception::multipleOutputSources(const string& name){
	string message = name + ": ambiguous output stream sources";
	throw new Exception(message);
}

void Exception::unexpectedArgument(const string& name, Token t){
	string message = name + ": unexpected argument " + t.value;
	throw new Exception(message);
}

void Exception::commandAllowedOnStart(const string& name){
	string message = name + ": command allowed only on the beggining of the pipeline ";
	throw new Exception(message);
}

void Exception::commandNotAllowedPipe(const string& name){
	string message = name + ": command is not allowed to be a part of the pipeline";
	throw new Exception(message);
}

void Exception::commandNotAllowedOutPipe(const string& name){
	string message = name + ": command should not have output source unless last in pipe";
	throw new Exception(message);
}

void Exception::commandNotAllowedInPipe(const string& name){
	string message = name + ": command should not have output source unless first in pipe";
	throw new Exception(message);
}
