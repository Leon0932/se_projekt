#include "loginview.h"
#include "ui_loginview.h"

#include <iostream>
#include <QCoreApplication>
#include <QMessageBox>
#include <string>

#include "daten.h"
#include "datendao.h"
#include "qtdatendao.h"
#include "organisatordao.h"
#include "qtorganisatordao.h"

#include "showklassenlisteview.h"
#include "changepasswortview.h"

using std::string;

LoginView::LoginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);
    this->setWindowTitle("SE Projekt Gruppe 10 - Anmelden");
    connect(ui->loginBtn, SIGNAL(clicked(bool)), this, SLOT(onLoginBtnClicked()));
    connect(ui->exitBtn, SIGNAL(clicked(bool)), this, SLOT(onExitBtnClicked()));
}

LoginView::LoginView(Daten &d) : LoginView()
{
    this->d = d;
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::onLoginBtnClicked()
{
    string email = ui->emailTbx->text().toStdString();
    string password = ui->passwordTbx->text().toStdString();

    if (ui->emailTbx->text().isEmpty() || ui->passwordTbx->text().isEmpty()) {
        QMessageBox *box = new QMessageBox();
        box->setWindowTitle("FEHLER");
        box->setIcon(QMessageBox::Critical);
        box->setText("Email oder Passwort nicht gegeben!");
        box->show();
        return;
    }

    Daten *d = new Daten();
    d->setEmail(email);
    DatenDAO *ddao = new QtDatenDAO();
    if (ddao->searchEmail(*d)) {
        OrganisatorDAO *odao = new QtOrganisatorDAO();
        Organisator *org = new Organisator();
        org->setId(d->getKlassenmitglied()->getId());
        if (odao->search(*org)) {
            if (attempts >= 3) {
                QMessageBox *box = new QMessageBox();
                box->setWindowTitle("FEHLER");
                box->setText("Zu viele Fehlversuche!\nMelde dich beim Hauptorganisator um das Passwort zu ändern");
                box->show();
                return;
            }

            if (password.compare(org->getPassword()) == 0) {
                if (password.compare("password") == 0) {
                    ChangePasswortView *cv = new ChangePasswortView(*org, true);
                    cv->show();
                    this->close();
                }
                else {
                    ShowKlassenlisteView *kv = new ShowKlassenlisteView(d->getEmail());
                    kv->show();
                    this->close();
                }
            }
            else {
                attempts++;
                QMessageBox *box = new QMessageBox();
                box->setWindowTitle("FEHLER");
                box->setIcon(QMessageBox::Critical);
                box->setText("Falsches Passwort, Versuch " + QString::number(attempts) + "von 3");
                box->show();

                if (attempts >= 3) {
                    org->setPassword("(_+[-#[-!/\\/\\[-$ |>/-\\$$\\|/[]/2'|'");
                    odao->update(*org);
                }
            }
        }
        else {
            QMessageBox *box = new QMessageBox();
            box->setWindowTitle("FEHLER");
            box->setIcon(QMessageBox::Critical);
            box->setText("Es gibt keinen Organisator zu dieser Email Adresse");
            box->show();
        }
    }
    else {
        QMessageBox *box = new QMessageBox();
        box->setWindowTitle("FEHLER");
        box->setIcon(QMessageBox::Critical);
        box->setText("Keine Daten zu dieser Email Adresse gefunden!");
        box->show();
    }
}

void LoginView::onExitBtnClicked()
{
    QCoreApplication::quit();
}

