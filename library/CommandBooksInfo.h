#pragma once
#include "Command.h"
#include "AuthorizeContext.h"
#include "FileContext.h"
#include "BookStore.h"

class CommandBooksInfo :
    public Command
{
private:
    const AuthorizeContext* auth;
    const FileContext* fileCtx;
    BookStore* bookStore;
public:
    CommandBooksInfo(const AuthorizeContext& auth, const FileContext& fileCtx, BookStore& bookStore);
    bool authorize() override;
    void execute(std::istream& in, std::ostream& out, const std::vector<std::string>& args) override;
};
