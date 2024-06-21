#include "serviceform.h"
#include "ui_serviceform.h"

ServiceForm::ServiceForm(QWidget *parent) :
    QWidget(parent),
    changeServiceWindow(new ChangeServiceWindow(parent)),
    ui(new Ui::ServiceForm)
{
    ui->setupUi(this);

    connect(ui->changeButton, &QPushButton::clicked, this, [this](){
        changeServiceWindow->show();
        changeServiceWindow->setId(id);
    });



    connect(ui->deleteButton, &QPushButton::clicked, this, [this](){

        QMessageBox deleteMsg;
        deleteMsg.setWindowTitle("Удаление сервиса");
        deleteMsg.setText("Вы точно хотите удалить данный сервис?");
        deleteMsg.setIcon(QMessageBox::Information);
        deleteMsg.setWindowIcon(QIcon(":/images/res/icons8-trash-50.png"));
        QPushButton *yesButton = deleteMsg.addButton(QString::fromUtf8("Да"), QMessageBox::YesRole);
        QPushButton *noButton = deleteMsg.addButton(QString::fromUtf8("Нет"), QMessageBox::NoRole);

        deleteMsg.setDefaultButton(noButton);

        deleteMsg.exec();

        if(deleteMsg.clickedButton() == yesButton)
        {
            if(SqlRequster::deleteService(id) != QueryResult::QUERY_OK)
            {
                QMessageBox::critical(this, "Ошибка!", "При выполнении запроса к бд, возникла ошибка");
                return;
            }

            QMessageBox::information(this, "Успешно", "Сервис удален! Обновите страницу чтобы увидеть изменения");
            ui->changeButton->hide();
            ui->deleteButton->hide();
        }


    });


    connect(ui->copyPassButton, &QPushButton::clicked, this, [this](){
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(ui->servicePassLabel->text());
    });


}

ServiceForm::~ServiceForm()
{
    delete ui;
}

void ServiceForm::setItems(const QString &serviceName,const QString &servicePass, int id)
{
    ui->serviceNameLabel->setText(serviceName);
    ui->servicePassLabel->setText(servicePass);
    this->id = id;
}
