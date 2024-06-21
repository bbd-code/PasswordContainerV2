#ifndef SQLREQUSTER_H
#define SQLREQUSTER_H

#include"QueryResult.h"
#include"user.h"
#include<QSqlQuery>
#include<QSqlError>
#include<QListWidget>
#include"serviceform.h"

struct SqlRequster
{
    static QueryResult authQuery(const User& user);

    static QueryResult registerQuery(const User& user);

    static QueryResult makeService(const User& user, const QString& serviceName, const QString& servicePassword);

    static QueryResult deleteService(const int id);

    static QueryResult deleteAllServices(const User& user);

    static QueryResult updateService(const int id, const QString& newServiceName, const QString& newServicePassword);

    static QueryResult showServices(const User& user, QListWidget*& widget);

    static QueryResult showServices(const QString& search, const User& user,QListWidget*& widget);

    static QueryResult deleteAccount(const User& user);
};

#endif // SQLREQUSTER_H
