#include "serviceswindow.h"
#include "ui_serviceswindow.h"

ServicesWindow::ServicesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServicesWindow)
{
    ui->setupUi(this);


    connect(ui->searchButton, &QPushButton::clicked, this, [this](){
        SqlRequster::showServices(ui->searchLine->text(), user,  ui->servicesListWidget);
    });


    connect(ui->refreshButton, &QPushButton::clicked, this, [this](){

        SqlRequster::showServices(user, ui->servicesListWidget);

    });

    connect(ui->deleteAllButton, &QPushButton::clicked, this, [this](){

        QMessageBox deleteMsg;
        deleteMsg.setWindowTitle("Удаление сервисов");
        deleteMsg.setText("Вы точно хотите удалить ВСЕ сервисы?");
        deleteMsg.setIcon(QMessageBox::Information);
        deleteMsg.setWindowIcon(QIcon(":/images/res/icons8-recycle-bin-64.png"));
        QPushButton *yesButton = deleteMsg.addButton(QString::fromUtf8("Да"), QMessageBox::YesRole);
        QPushButton *noButton = deleteMsg.addButton(QString::fromUtf8("Нет"), QMessageBox::NoRole);

        deleteMsg.setDefaultButton(noButton);

        deleteMsg.exec();

        if(deleteMsg.clickedButton() == yesButton)
        {
            if(SqlRequster::deleteAllServices(user) != QueryResult::QUERY_OK)
            {
                QMessageBox::critical(this, "Ошибка!", "При выполнении запроса к бд, возникла ошибка");
                return;
            }

            QMessageBox::information(this, "Успешно", "ВСЕ сервисы удалены!");
        }

    });
}

ServicesWindow::~ServicesWindow()
{
    delete ui;
}

void ServicesWindow::setUser(User user)
{
    this->user = user;
}

void ServicesWindow::clear()
{
    ui->searchLine->clear();
    ui->servicesListWidget->clear();
}





