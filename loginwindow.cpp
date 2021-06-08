#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <iostream>
#include <QCoreApplication>
#include <string>

#include "daten.h"
#include "datendao.h"
#include "qtdatendao.h"

using std::string;

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->loginBtn, SIGNAL(clicked(bool)), this, SLOT(onLoginBtnClicked()));
    connect(ui->exitBtn, SIGNAL(clicked(bool)), this, SLOT(onExitBtnClicked()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onLoginBtnClicked()
{
    std::cout << "login clicked" << std::endl;
    string email = ui->emailTbx->text().toStdString();
    string password = ui->passwordTbx->text().toStdString();

    Daten d = Daten();
    d.setEmail(email);
    DatenDAO *ddao = new QtDatenDAO();
    ddao->searchEmail(d);

    std::cout << d.getNachname() << std::endl;
    std::cout << d.getTimestamp() << std::endl;
}

void LoginWindow::onExitBtnClicked()
{
    QCoreApplication::quit();
}

