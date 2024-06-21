#include "user.h"



QString User::getEmail() const
{
    return email;
}

void User::setEmail(const QString &newEmail)
{
    email = newEmail;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &newPassword)
{
    password = newPassword;
}

void User::dropData()
{
    email.clear();
    password.clear();
}

