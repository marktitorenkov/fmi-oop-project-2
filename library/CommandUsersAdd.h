#pragma once
#include "Command.h"
#include "AuthorizeContext.h"
#include "UserStore.h"

class CommandUsersAdd :
    public Command
{
public:
    CommandUsersAdd(AuthorizeContext const& auth, UserStore& userStore);
    bool authorize() override;
    void execute(std::istream& in, std::ostream& out, const std::vector<std::string>& args) override;
private:
    AuthorizeContext const& auth;
    UserStore& userStore;
};