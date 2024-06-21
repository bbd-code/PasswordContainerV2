#include "changeservicewindow.h"
#include "ui_changeservicewindow.h"

ChangeServiceWindow::ChangeServiceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChangeServiceWindow)
{
    ui->setupUi(this);

    connect(ui->changeButton, &QPushButton::clicked, this, [this](){
        if(ui->serviceNameLine->text().isEmpty() && ui->servicePassword->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка!", "Только одна строка может быть пустой.\nИзмените название сервиса, либо пароль или же все сразу!");
            return;
        }

        if(SqlRequster::updateService(id, ui->serviceNameLine->text(), ui->servicePassword->text()) != QueryResult::QUERY_OK)
        {
            QMessageBox::critical(this ,"Ошибка!", "При выполнении запроса к бд, возникла ошибка");
            return;
        }

        QMessageBox::information(this, "Успешно!", "Сервис изменен. Чтобы увидеть изменение, введите сервис в поиске, либо нажмите на обновить");
    });
}

ChangeServiceWindow::~ChangeServiceWindow()
{
    delete ui;
}

int ChangeServiceWindow::getId() const
{
    return id;
}

void ChangeServiceWindow::setId(int newId)
{
    id = newId;
}
