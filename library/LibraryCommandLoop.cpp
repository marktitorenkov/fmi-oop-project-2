#include <sstream>
#include "LibraryCommandLoop.h"

#include "Command.h"
#include "CommandBooksAdd.h"
#include "CommandBooksAll.h"
#include "CommandBooksFind.h"
#include "CommandBooksInfo.h"
#include "CommandBooksSort.h"
#include "CommandClose.h"
#include "CommandExit.h"
#include "CommandHelp.h"
#include "CommandLogin.h"
#include "CommandLogout.h"
#include "CommandOpen.h"
#include "CommandSave.h"
#include "CommandSaveAs.h"
#include "CommandUsersAdd.h"
#include "CommandUsersRemove.h"

LibraryCommandLoop::LibraryCommandLoop(std::istream& in, std::ostream& out, AuthorizeContext& authCtx, BookStore& bookStore, UserStore& userStore) :
    in(in),
    out(out),
    running(false),
    commands{
        new CommandOpen,
        new CommandClose,
        new CommandSave,
        new CommandSaveAs,

        new CommandLogin{ authCtx, userStore },
        new CommandLogout{ authCtx },

        new CommandBooksAdd{ authCtx, bookStore },
        new CommandBooksAll{ authCtx, bookStore },
        new CommandBooksFind{ authCtx, bookStore },
        new CommandBooksInfo{ authCtx, bookStore },
        new CommandBooksSort{ authCtx, bookStore },

        new CommandUsersAdd{ authCtx, userStore},
        new CommandUsersRemove{ authCtx, userStore},

        new CommandHelp{ this },
        new CommandExit{ this },
    }
{
}

void LibraryCommandLoop::Start()
{
    if (!running)
    {
        running = true;
        loop();
    }
}

void LibraryCommandLoop::Stop()
{
    running = false;
}

const std::vector<Command*>& LibraryCommandLoop::getCommands() const
{
    return commands;
}

void LibraryCommandLoop::loop()
{
    while (running)
    {
        out << "> ";
        std::string line;
        std::getline(in, line);

        std::istringstream linestream{ line };
        std::string commandStr;
        if (linestream >> commandStr)
        {
            Command* command = nullptr;
            for (Command* const& c : commands)
            {
                if (c->getName() == commandStr)
                {
                    command = c;
                }
            }

            if (command)
            {
                std::vector<std::string> args = parseArgs(linestream, command->getMinArgsCount());
                if (args.size() != command->getMinArgsCount())
                {
                    out << "Expected " << command->getMinArgsCount() << " argument(s) but got " << args.size() << "." << std::endl;
                }
                else if (!command->authorize())
                {
                    out << "You are not authorized to perform this action." << std::endl;
                }
                else
                {
                    command->execute(in, out, args);
                }
            }
            else
            {
                out << "Unknown command \"" << commandStr << "\"." << std::endl;
            }
        }
    }
}

std::vector<std::string> LibraryCommandLoop::parseArgs(std::istringstream& linestream, unsigned int max)
{
    std::vector<std::string> args;
    std::string token;
    for (unsigned int i = 0; i < max && linestream >> token; i++)
    {
        args.push_back(token);
    }
    return args;
}
