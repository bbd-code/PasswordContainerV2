#ifndef SERVICESWINDOW_H
#define SERVICESWINDOW_H

#include <QMainWindow>
#include"sqlrequster.h"

namespace Ui {
class ServicesWindow;
}

class ServicesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServicesWindow(QWidget *parent = nullptr);
    ~ServicesWindow();
    void setUser(User user);

    void clear();


private:
    Ui::ServicesWindow *ui;
    User user;
};

#endif // SERVICESWINDOW_H
