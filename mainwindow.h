#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<QSqlDatabase>
#include<QIntValidator>
#include"sqlrequster.h"
#include"serviceswindow.h"
#include"addservicewindow.h"
#include"emailsender.h"
#include"settingssaver.h"
#include"inputvalidation.h"
#include<windows.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void clearAppAfterLogoutOrRemove();

private:
    Ui::MainWindow *ui;
    ServicesWindow* servicesWindow;
    AddServiceWindow* addServiceWindow;
    QSqlDatabase dbConnection;
    User user;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
