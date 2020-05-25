#include "UserStore.h"

void UserStore::Add(const User& user)
{
    if (!getByUsername(user.getUsername()))
    {
        users.push_back(new User(user));
    }
}

User* UserStore::getByUsername(const std::string& username)
{
    for (User* const& u : users)
    {
        if (u->getUsername() == username)
        {
            return u;
        }
    }

    return nullptr;
}

void UserStore::RemoveByUsername(const std::string& username)
{
    for (auto i = users.begin(); i != users.end(); i++)
    {
        if ((*i)->getUsername() == username)
        {
            users.erase(i);
            return;
        }
    }
}
