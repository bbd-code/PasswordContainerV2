#ifndef USER_H
#define USER_H

#include<QString>

class User
{

public:


    QString getEmail() const;
    void setEmail(const QString &newEmail);
    QString getPassword() const;
    void setPassword(const QString &newPassword);

    void dropData();


private:

    QString email;
    QString password;


};

#endif // USER_H
