#include "sqlrequster.h"




QueryResult SqlRequster::authQuery(const User& user)
{
    QSqlQuery query;

    query.prepare("SELECT user_email, user_password FROM users WHERE user_email=\'" + user.getEmail() + "\'" );

    if(query.exec())
    {
        query.next();

        QString responsedEmail = query.value(0).toString();
        QString responsedPass = query.value(1).toString();

        if(responsedEmail.isEmpty())
        {
            return QueryResult::QUERY_SELECT_EMPTY;
        }
        else if(responsedPass != user.getPassword())
        {
            return QueryResult::QUERY_INCORRECT_PASS;
        }


        if(responsedEmail == user.getEmail() && responsedPass == user.getPassword())
        {
            return QueryResult::QUERY_OK;
        }
    }

    qDebug() << query.lastError().text()  << "\n";
    return QueryResult::QUERY_GENERIC_ERROR;
}



QueryResult SqlRequster::registerQuery(const User& user)
{
    QSqlQuery query;




    if(query.exec("INSERT INTO users(user_email, user_password) VALUES(\'" + user.getEmail() + "\' , \'" + user.getPassword() + "\')"))
        return QueryResult::QUERY_OK;

    if(query.lastError().text().contains("UNIQUE") || query.lastError().text().contains("unique")){
        return QueryResult::QUERY_UNIQUE_FAIL;
    }

    qDebug() << query.lastError().text()  << "\n";
    return QueryResult::QUERY_GENERIC_ERROR;
}





QueryResult SqlRequster::makeService(const User& user,const QString &serviceName, const QString &servicePassword)
{
    QSqlQuery query;

    if(query.exec("INSERT INTO services(user_id, service_name, service_password)"
                   " VALUES((SELECT id FROM users WHERE user_email =\'" + user.getEmail()  + "\'),\'" + serviceName + "\',\'"+ servicePassword +"\')"))
    {return QueryResult::QUERY_OK;}


    qDebug() << query.lastError().text()  << "\n";
    return QueryResult::QUERY_GENERIC_ERROR;


}



QueryResult SqlRequster::updateService(const int id, const QString& newServiceName, const QString& newServicePassword)
{
    QSqlQuery query;

    QString queryText;


    if(newServicePassword.isEmpty() && !newServiceName.isEmpty())
    {
        queryText = "UPDATE services SET service_name = \'" + newServiceName + "\' WHERE id = \'" + QString::number(id) +"\'";
    }
    else if(!newServicePassword.isEmpty() && newServiceName.isEmpty())
    {
        queryText = "UPDATE services SET service_password = \'" + newServicePassword + "\' WHERE id = \'" + QString::number(id) +"\'";
    }
    else
    {
        queryText = "UPDATE services SET service_name=\'" + newServiceName + "\', service_password = \'" + newServicePassword + "\' WHERE id = \'" + QString::number(id) +"\'";
    }

    if(query.exec(queryText))
    {
        return QueryResult::QUERY_OK;
    }

    qDebug() << query.lastError().text()  << "\n";
    return QueryResult::QUERY_GENERIC_ERROR;

}

QueryResult SqlRequster::deleteService(const int id)
{
    QSqlQuery query;

    if(query.exec("DELETE FROM services WHERE id=\'" + QString::number(id) + "\'"))
    {
        return QueryResult::QUERY_OK;
    }

    qDebug() << query.lastError().text()  << "\n";
    return QueryResult::QUERY_GENERIC_ERROR;

}

QueryResult SqlRequster::deleteAllServices(const User& user)
{
    QSqlQuery query;

    if(query.exec("DELETE FROM services WHERE user_id=(SELECT id FROM users WHERE user_email=\'" + user.getEmail() + "\')"))
    {
        return QueryResult::QUERY_OK;
    }

    qDebug() << query.lastError().text()  << "\n";
    return QueryResult::QUERY_GENERIC_ERROR;
}

QueryResult SqlRequster::showServices(const User& user, QListWidget*& widget)
{
    QSqlQuery query;

    if(widget->children().size() > 0)
        widget->clear();


    if(query.exec("SELECT id, service_name, service_password from services WHERE user_id=(SELECT id FROM users WHERE user_email=\'" + user.getEmail() + "\')"))
    {


        while(query.next())
        {
            QListWidgetItem *item = new QListWidgetItem;
            ServiceForm *serviceForm = new ServiceForm;
            serviceForm->setItems(query.value(1).toString(), query.value(2).toString() ,query.value(0).toInt());
            widget->addItem(item);
            item->setSizeHint(QSize(500, 200));
            widget->setItemWidget(item, serviceForm);
        }
        return QueryResult::QUERY_OK;
    }

    qDebug() << query.lastError().text()  << "\n";
    return QueryResult::QUERY_GENERIC_ERROR;
}

QueryResult SqlRequster::showServices(const QString& search, const User& user, QListWidget*& widget)
{
    QSqlQuery query;

    if(widget->children().size() > 0)
        widget->clear();


    if(query.exec("SELECT id, service_name, service_password from services WHERE user_id=(SELECT id FROM users WHERE user_email=\'" + user.getEmail() + "\') "
                                "AND service_name LIKE \'%" + search + "%\'"))
    {


        while(query.next())
        {
            QListWidgetItem *item = new QListWidgetItem;
            ServiceForm *serviceForm = new ServiceForm;
            serviceForm->setItems(query.value(1).toString(), query.value(2).toString() ,query.value(0).toInt());
            widget->addItem(item);
            item->setSizeHint(QSize(500, 200));
            widget->setItemWidget(item, serviceForm);
        }
        return QueryResult::QUERY_OK;
    }

    qDebug() << query.lastError().text()  << "\n";
    return QueryResult::QUERY_GENERIC_ERROR;
}



QueryResult SqlRequster::deleteAccount(const User &user)
{

    QSqlQuery queryDeleteAccount;
    QSqlQuery queryDeleteAccountServices;


    if(queryDeleteAccountServices.exec("DELETE FROM services WHERE user_id=(SELECT id FROM users WHERE user_email=\'" + user.getEmail() + "\')"))
    {
        if(queryDeleteAccount.exec("DELETE FROM users WHERE user_email=\'" + user.getEmail() + "\'"))
        {
            return QueryResult::QUERY_OK;
        }
    }





    qDebug() << "delete user services error: " << queryDeleteAccountServices.lastError().text()  << "delete user error:" << queryDeleteAccount.lastError().text() << "\n";
    return QueryResult::QUERY_GENERIC_ERROR;
}







