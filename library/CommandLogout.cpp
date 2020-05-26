#include "CommandLogout.h"

CommandLogout::CommandLogout(AuthorizeContext& auth) :
    Command("logout", 0, "logout"),
    auth(auth)
{
}

bool CommandLogout::authorize()
{
    return auth.getActiveUser();
}

void CommandLogout::execute(std::ostream& out, const std::vector<std::string>& args)
{
    auth.setActiveUser(nullptr);
    out << "Succesfully logged out" << std::endl;
}
