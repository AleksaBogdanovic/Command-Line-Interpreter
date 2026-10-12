#include "Program.h"

Program* Program::s_instance = nullptr;

Program::Program() {}

Program* Program::Instance()
{
    if (s_instance == nullptr) {
        s_instance = new Program();
    }

    return s_instance;
}

void Program::add(Command* cmd){
    commands.push_back(cmd);
    if (commands.size() == 1)   it = commands.begin();
}

void Program::executeNext() {
    (*it)->execute();
    it++;
}

bool Program::hasNext() {
    return it != commands.end();
}


