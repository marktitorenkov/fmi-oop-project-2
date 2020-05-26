#include "CommandClose.h"

CommandClose::CommandClose() :
    Command("close", 0, "closes currently opened file")
{
}

bool CommandClose::authorize()
{
    return true;
}

void CommandClose::execute(std::ostream& out, const std::vector<std::string>& args)
{
    out << "close executed" << std::endl;
}
