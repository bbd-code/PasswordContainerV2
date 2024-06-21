#ifndef ADDSERVICEWINDOW_H
#define ADDSERVICEWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include"sqlrequster.h"


namespace Ui {
class AddServiceWindow;
}

class AddServiceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddServiceWindow(QWidget *parent = nullptr);
    ~AddServiceWindow();


    void setUser(User user);

    void clear();
private:
    Ui::AddServiceWindow *ui;
    User user;
};

#endif // ADDSERVICEWINDOW_H
