#include "loginview.h"
#include "ui_loginview.h"

#include <iostream>
#include <QCoreApplication>
#include <string>

#include "daten.h"
#include "datendao.h"
#include "qtdatendao.h"

using std::string;

LoginView::LoginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);
    connect(ui->loginBtn, SIGNAL(clicked(bool)), this, SLOT(onLoginBtnClicked()));
    connect(ui->exitBtn, SIGNAL(clicked(bool)), this, SLOT(onExitBtnClicked()));
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::onLoginBtnClicked()
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

void LoginView::onExitBtnClicked()
{
    QCoreApplication::quit();
}

