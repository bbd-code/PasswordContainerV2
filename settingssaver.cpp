#include "settingssaver.h"

QSettings * SettingsSaver::settings = new QSettings("BBD", "PasswordContainer");




void SettingsSaver::showSavedData()
{
    qDebug() << settings->allKeys();
}

void SettingsSaver::saveUserEmail(const QString &userEmail)
{
    settings->setValue("savedEmail", userEmail);
}

QString SettingsSaver::getUserEmail()
{
    return settings->value("savedEmail").toString();
}

void SettingsSaver::dropData()
{
    settings->clear();
}

void SettingsSaver::deleteFromMemory(){

    delete settings;
}
