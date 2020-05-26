#include "CommandExit.h"

CommandExit::CommandExit(IStoppable* loop) :
    Command("exit", 0, "exists the program"),
    _loop(loop)
{
}

bool CommandExit::authorize()
{
    return true;
}

void CommandExit::execute(std::istream& in, std::ostream& out, const std::vector<std::string>& args)
{
    _loop->Stop();
    out << "Exiting the program..." << std::endl;
}
