#ifndef SETTINGSSAVER_H
#define SETTINGSSAVER_H


#include<QSettings>

class SettingsSaver
{
public:


    static void showSavedData();

    static void saveUserEmail(const QString& userEmail);

    static QString getUserEmail();

    static void dropData();

    static void deleteFromMemory();
private:

    static QSettings * settings;

};

#endif // SETTINGSSAVER_H
