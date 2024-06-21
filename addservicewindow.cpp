#include "addservicewindow.h"
#include "ui_addservicewindow.h"

AddServiceWindow::AddServiceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddServiceWindow)
{
    ui->setupUi(this);



    connect(ui->addButton, &QPushButton::clicked, this, [this](){

        if(ui->serviceNameLine->text().isEmpty() || ui->servicePassword->text().isEmpty())
        {
            QMessageBox::critical(this, "Ошибка!", "Данные сервиса должны быть заполнены!");

            return;
        }

        if(SqlRequster::makeService(user, ui->serviceNameLine->text(), ui->servicePassword->text()) != QueryResult::QUERY_OK){

            QMessageBox::critical(this, "Ошибка!", "Ошибка при выполнении запроса");

            return;
        }


        QMessageBox::information(this, "Успешно", "Сервис " + ui->serviceNameLine->text() + " добавлен!");
    });

}

AddServiceWindow::~AddServiceWindow()
{
    delete ui;
}

void AddServiceWindow::setUser(User user)
{
    this->user = user;
}

void AddServiceWindow::clear()
{
    ui->serviceNameLine->clear();
    ui->servicePassword->clear();
}
