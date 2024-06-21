#ifndef SERVICEFORM_H
#define SERVICEFORM_H

#include"changeservicewindow.h"
#include <QWidget>
#include<QListWidgetItem>
#include<QClipboard>

class ChangeServiceWindow;

namespace Ui {
class ServiceForm;
}

class ServiceForm : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceForm(QWidget *parent = nullptr);
    ~ServiceForm();

    void setItems(const QString& serviceName,const QString& servicePass, int id);


private:
    Ui::ServiceForm *ui;
    ChangeServiceWindow* changeServiceWindow;

    int id;
};

#endif // SERVICEFORM_H
