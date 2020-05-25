#pragma once
#include "Command.h"

class CommandSave :
    public Command
{
public:
    CommandSave();
    bool authorize(bool userIsLoggedIn, bool userIsAdmin) override;
    void execute(std::ostream& out, const std::vector<std::string>& args) override;
};
