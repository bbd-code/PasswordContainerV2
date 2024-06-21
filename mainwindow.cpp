#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , servicesWindow(new ServicesWindow(this))
    , addServiceWindow(new AddServiceWindow(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //someSetups

    QIntValidator* validator = new QIntValidator(100000, 999999, this);
    ui->codeLine->setValidator(validator);

    dbConnection = QSqlDatabase::addDatabase("QSQLITE");

    dbConnection.setDatabaseName("PassCont.db");
    dbConnection.setHostName("localhost");
    dbConnection.setPassword("12345");
    dbConnection.setUserName("");

    if(!dbConnection.open()){
        QMessageBox::critical(this, "Ошибка", "Ошибка подключения к базе данных : " + dbConnection.lastError().text());
        return;
    }





    //hello-page

    if(SettingsSaver::getUserEmail() != "")
    {
        ui->emailLabel->setText(SettingsSaver::getUserEmail());
        user.setEmail(SettingsSaver::getUserEmail());
        ui->pageGroupMainWindow->setCurrentWidget(ui->mainPage);
    }


    connect(ui->toAuthButton, &QPushButton::clicked, this, [this](){
        ui->pageGroupMainWindow->setCurrentWidget(ui->registerAndAuthPage);
        ui->pageGroupAuthRegister->setCurrentWidget(ui->authPage);
    });

    connect(ui->toRegisterButton, &QPushButton::clicked, this, [this](){
        ui->pageGroupMainWindow->setCurrentWidget(ui->registerAndAuthPage);
        ui->pageGroupAuthRegister->setCurrentWidget(ui->registerPage);
    });

    connect(ui->programSettingsButton, &QPushButton::clicked, this, [this](){

        ui->pageGroupMainWindow->setCurrentWidget(ui->programSettingsPage);

    });


    //programSettingsPage

    connect(ui->readyButton, &QPushButton::clicked, this, [this](){

        dbConnection = QSqlDatabase::addDatabase(ui->dbDriver->currentIndex() == 0 ? "QPSQL" : "QSQLITE");

        dbConnection.setDatabaseName(ui->dbName->text());
        dbConnection.setHostName(ui->dbHost->text());
        dbConnection.setPassword(ui->dbPass->text());
        dbConnection.setUserName(ui->dbUser->text());

        if(!dbConnection.open()){
            QMessageBox::critical(this, "Ошибка", "Ошибка подключения к базе данных : " + dbConnection.lastError().text());
            return;
        }

        QMessageBox::information(this, "Успешно", "Подключение с бд установлено!");



    });

    connect(ui->backToHelloPageButton, &QPushButton::clicked, this, [this](){
        ui->pageGroupMainWindow->setCurrentWidget(ui->helloPage);

    });



    //authPage, registerPage, checkBox
    connect(ui->authButton, &QPushButton::clicked, this, [this](){

        if(ui->emailLine->text().isEmpty() || ui->passLine->text().isEmpty())
        {
            QMessageBox::critical(this ,"Ошибка!", "Строки с данными не должны быть пустыми!");
            return;
        }

        if((InputValidation::validateEmail(ui->emailLine->text()) != QValidator::Acceptable) || (InputValidation::validatePassword(ui->passLine->text()) != QValidator::Acceptable)){
            QMessageBox::critical( this,"Ошибка!", "Данные введены некорректно!");
            return;
        }

        user.setEmail(ui->emailLine->text());
        user.setPassword(ui->passLine->text());


        switch (SqlRequster::authQuery(user))
        {

        case QueryResult::QUERY_SELECT_EMPTY:

              QMessageBox::critical(this,"Ошибка!", "Пользователя с таким email нет в базе данных!");
            return;

        case QueryResult::QUERY_GENERIC_ERROR:

             QMessageBox::critical( this,"Ошибка!", "При выполнении запроса к бд, возникла ошибка :[" + dbConnection.lastError().text() + "]");
            return;

        case QueryResult::QUERY_INCORRECT_PASS:
            QMessageBox::critical( this,"Ошибка!", "Введен неправильный пароль!");
            return;

        }


        if(!EmailSender::sendEmailCode(user.getEmail().toStdString())){
            QMessageBox::critical( this,"Ошибка!", "Ошибка при отправке кода подтверждения!");
        }

        ui->codeEmailLabel->setText(ui->emailLine->text());
        ui->pageGroupMainWindow->setCurrentWidget(ui->enterCodePage);

    });


    connect(ui->registerButton, &QPushButton::clicked, this, [this](){

        if(ui->emailLine->text().isEmpty() || ui->passLine->text().isEmpty())
        {
            QMessageBox::critical(this ,"Ошибка!", "Строки с данными не должны быть пустыми!");
            return;
        }

        if((InputValidation::validateEmail(ui->emailLine->text()) != QValidator::Acceptable) || (InputValidation::validatePassword(ui->passLine->text()) != QValidator::Acceptable)){
            QMessageBox::critical( this,"Ошибка!", "Данные введены не корректно!");
            return;
        }

        user.setEmail(ui->emailLine->text());
        user.setPassword(ui->passLine->text());

        switch(SqlRequster::registerQuery(user))
        {
        case QueryResult::QUERY_UNIQUE_FAIL:
            QMessageBox::critical(this ,"Ошибка!", "Пользователь с таким email уже есть в базе!");
            return;

        case QueryResult::QUERY_GENERIC_ERROR:
            QMessageBox::critical(this ,"Ошибка!", "При выполнении запроса к бд, возникла ошибка :[" + dbConnection.lastError().text() + "]");
            return;
        }


        if(!EmailSender::sendEmailCode(user.getEmail().toStdString())){
            QMessageBox::critical(this, "Ошибка!", "Ошибка при отправке кода подтверждения!");
        }

        ui->pageGroupMainWindow->setCurrentWidget(ui->enterCodePage);
        ui->codeEmailLabel->setText(ui->emailLine->text());

    });


        connect(ui->showPasswordCheckBox, &QCheckBox::stateChanged, this, [this](){
        if(ui->showPasswordCheckBox->isChecked())
        {
            ui->passLine->setEchoMode(QLineEdit::Normal);
            return;
        }
        ui->passLine->setEchoMode(QLineEdit::Password);
    });

    connect(ui->switchRegisterButton, &QPushButton::clicked, this, [this](){

        ui->pageGroupAuthRegister->setCurrentWidget(ui->registerPage);

    });


    connect(ui->switchAuthButton, &QPushButton::clicked, this, [this](){

        ui->pageGroupAuthRegister->setCurrentWidget(ui->authPage);

    });

    connect(ui->emailLine, &QLineEdit::textChanged, this, [this](){

        switch(InputValidation::validateEmail(ui->emailLine->text())){

        case QValidator::Acceptable:

            ui->emailLine->setStyleSheet("border: 2px solid white");
            ui->emailLine->setToolTip("Email введен корректно");
            break;

        case QValidator::Invalid:
        case QValidator::Intermediate:
            ui->emailLine->setStyleSheet("border: 2px solid red;");
            ui->emailLine->setToolTip("Email введён неверно");
            break;

        }

    });

    connect(ui->passLine, &QLineEdit::textChanged, this, [this](){

        switch(InputValidation::validatePassword(ui->passLine->text())){

        case QValidator::Acceptable:

            ui->passLine->setStyleSheet("border: 2px solid white");
            ui->passLine->setToolTip("Пароль введен корректно");
            break;

        case QValidator::Invalid:
        case QValidator::Intermediate:
            ui->passLine->setStyleSheet("border: 2px solid red;");
            ui->passLine->setToolTip("Пароль введён неверно. Минимум 7 символов");
            break;

        }

    });

    connect(ui->toHelloPageButton, &QPushButton::clicked, this, [this](){

        ui->pageGroupMainWindow->setCurrentWidget(ui->helloPage);

    });


    //enterCodePage


    connect(ui->codeReadyButton, &QPushButton::clicked, this, [this](){



        if(EmailSender::getCode() == ui->codeLine->text().toStdString())
        {
            user.setEmail(ui->emailLine->text());
            user.setPassword(ui->passLine->text());

            if(ui->rememberMeCheckBox->isChecked()){
                SettingsSaver::saveUserEmail(user.getEmail());
            }

            ui->pageGroupMainWindow->setCurrentWidget(ui->mainPage);
            ui->emailLabel->setText(user.getEmail());
            return;
        }

        QMessageBox::critical(this,"Ошибка!", "Неверный код подтверждения!");

    });


    //mainPage

    connect(ui->makeServiceButton, &QPushButton::clicked, this, [this](){

        addServiceWindow->show();
        addServiceWindow->setUser(user);
    });

    connect(ui->showServices, &QPushButton::clicked, this, [this](){
        servicesWindow->show();
        servicesWindow->setUser(user);
    });

    connect(ui->logoutButton, &QPushButton::clicked, this, [this](){

        QMessageBox logoutMsg;
        logoutMsg.setWindowTitle("Выход из аккаунта");
        logoutMsg.setText("Вы точно хотите выйти?");
        logoutMsg.setIcon(QMessageBox::Information);
        logoutMsg.setWindowIcon(QIcon(":/images/res/icons8-logout-50.png"));
        QPushButton *yesButton = logoutMsg.addButton(QString::fromUtf8("Да"), QMessageBox::YesRole);
        QPushButton *noButton = logoutMsg.addButton(QString::fromUtf8("Нет"), QMessageBox::NoRole);

        logoutMsg.setDefaultButton(noButton);

        logoutMsg.exec();

        if(logoutMsg.clickedButton() == yesButton)
        {

            SettingsSaver::dropData();


            clearAppAfterLogoutOrRemove();

            ui->pageGroupMainWindow->setCurrentWidget(ui->helloPage);
        }






    });

    connect(ui->deleteAccountButton, &QPushButton::clicked, this, [this](){

        QMessageBox deleteAccountMsg;
        deleteAccountMsg.setWindowTitle("Удаление аккаунта");
        deleteAccountMsg.setText("Вы точно хотите УДАЛИТЬ аккаунт?\nДействие НЕЛЬЗЯ отменить!");
        deleteAccountMsg.setIcon(QMessageBox::Information);
        deleteAccountMsg.setWindowIcon(QIcon(":/images/res/icons8-remove-user-50.png"));
        QPushButton *yesButton = deleteAccountMsg.addButton(QString::fromUtf8("Да"), QMessageBox::YesRole);
        QPushButton *noButton = deleteAccountMsg.addButton(QString::fromUtf8("Нет"), QMessageBox::NoRole);

        deleteAccountMsg.setDefaultButton(noButton);

        deleteAccountMsg.exec();

        if(deleteAccountMsg.clickedButton() == yesButton)
        {
            if(SqlRequster::deleteAccount(user) != QueryResult::QUERY_OK)
            {
                QMessageBox::critical(this, "Ошибка!", "При выполнении запроса к бд, возникла ошибка");
                return;
            }

            QMessageBox::information(this, "Успешно", "Ваш аккаунт удален!");
            SettingsSaver::dropData();

            clearAppAfterLogoutOrRemove();

            ui->pageGroupMainWindow->setCurrentWidget(ui->helloPage);
        }

    });


}

MainWindow::~MainWindow()
{
    dbConnection.close();
    SettingsSaver::deleteFromMemory();
    delete servicesWindow;
    delete ui;
}

void MainWindow::clearAppAfterLogoutOrRemove()
{
    ui->emailLine->clear();
    ui->passLine->clear();
    ui->passLine->setEchoMode(QLineEdit::EchoMode::Password);
    ui->codeLine->clear();
    ui->rememberMeCheckBox->setChecked(false);
    ui->showPasswordCheckBox->setChecked(false);
    user.dropData();
    servicesWindow->clear();
    addServiceWindow->clear();

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    servicesWindow->close();
    addServiceWindow->close();
}

