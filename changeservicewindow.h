#ifndef CHANGESERVICEWINDOW_H
#define CHANGESERVICEWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include"sqlrequster.h"

namespace Ui {
class ChangeServiceWindow;
}

class ChangeServiceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangeServiceWindow(QWidget *parent = nullptr);
    ~ChangeServiceWindow();



    int getId() const;
    void setId(int newId);

private:
    Ui::ChangeServiceWindow *ui;
    int id;
};

#endif // CHANGESERVICEWINDOW_H
