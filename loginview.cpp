#include "loginview.h"
#include "ui_loginview.h"

#include <iostream>
#include <QCoreApplication>
#include <string>

#include "daten.h"
#include "datendao.h"
#include "qtdatendao.h"
#include "organisatordao.h"
#include "qtorganisatordao.h"

#include "showklassenlisteview.h"

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
    string email = ui->emailTbx->text().toStdString();
    string password = ui->passwordTbx->text().toStdString();

    Daten d = Daten();
    d.setEmail(email);
    DatenDAO *ddao = new QtDatenDAO();
    if (ddao->searchEmail(d)) {
        OrganisatorDAO *odao = new QtOrganisatorDAO();
        Organisator org = Organisator();
        org.setId(d.getId());
        if (odao->search(org)) {
            if (password.compare(org.getPassword()) == 0) {
                ShowKlassenlisteView *kv = new ShowKlassenlisteView();
                kv->show();
                this->close();
            }
        }
    }
}

void LoginView::onExitBtnClicked()
{
    QCoreApplication::quit();
}

