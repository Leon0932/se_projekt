#include "createhauptorganisatorview.h"
#include "ui_createhauptorganisatorview.h"

#include "datendao.h"
#include "qtdatendao.h"

#include "QMessageBox"

#include "hauptorganisatordao.h"
#include "qthauptorganisatordao.h"
#include "hauptorganisator.h"

#include "klassenmitglieddao.h"
#include "qtklassenmitglieddao.h"

#include "qtkontaktdao.h"

#include "loginview.h"
#include "kontaktview.h"
#include "organisatordao.h"
#include "qtorganisatordao.h"

#include <iostream>
#include <string>
using std::string;

//Standardkonstruktor um den Fenstertitel zu setzen und die Signals und die Slots zu verbinden
CreateHauptorganisatorView::CreateHauptorganisatorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateHauptorganisatorView)
{
    ui->setupUi(this);
    this->setWindowTitle("SE Projekt Gruppe 10 - Hauptorganisator erstellen");
    connect(ui->kontakteBtn, SIGNAL(clicked(bool)), this, SLOT(onKontakteBtnClicked()));
    connect(ui->saveBtn, SIGNAL(clicked(bool)), this, SLOT(onSaveBtnClicked()));
    connect(ui->exitBtn, SIGNAL(clicked(bool)), this, SLOT(onExitBtnClicked()));
}

CreateHauptorganisatorView::~CreateHauptorganisatorView()
{
    delete ui;
}

//öffnet das Kontakte Fenster
void CreateHauptorganisatorView::onKontakteBtnClicked()
{
    KontaktView *kv = new KontaktView(kontaktList, hauptKontaktPos);
    kv->show();
}

//überprüft ob das email Feld leer ist, wenn nicht wird der Hauptorganisator und seine Daten usw. angelegt
void CreateHauptorganisatorView::onSaveBtnClicked()
{
    string name = ui->vornameTbx->text().toStdString();
    string nachname = ui->nachnameTbx->text().toStdString();
    string geburtsname = ui->geburtsnameTbx->text().toStdString();
    string email = ui->emailTbx->text().toStdString();
    string land = ui->landTbx->text().toStdString();
    int plz = ui->plzTbx->text().toInt();
    string ort = ui->ortTbx->text().toStdString();
    string strasse = ui->strasseTbx->text().toStdString();
    int hnr = ui->hausnummerTbx->text().toInt();

    if (email.empty()) {
        QMessageBox *box = new QMessageBox();
        box->setIcon(QMessageBox::Critical);
        box->setWindowTitle("FEHLER");
        box->setText("Email Adresse darf nicht leer sein");
        box->show();
        return;
    }

    Hauptorganisator hr = Hauptorganisator();

    KlassenmitgliedDAO *kdao = new QtKlassenmitgliedDAO();
    kdao->insert(hr);

    OrganisatorDAO *odao = new QtOrganisatorDAO();
    odao->insert(hr);

    HauptorganisatorDAO *hdao = new QtHauptorganisatorDAO();
    hdao->insert(hr);

    Daten d = Daten(nachname, name, geburtsname, hnr, ort, land, plz, strasse, email, "");
    d.setKlassenmitglied(&hr);
    d.setOrganisator(&hr);
    DatenDAO *ddao = new QtDatenDAO();
    if (ddao->insert(d)) {
        LoginView *lv = new LoginView();
        lv->show();
        this->close();
    }

    KontaktDAO *kodao = new QtKontaktDAO();
    for (auto const& k : this->kontaktList) {
        k->setDaten(&d);
        kodao->insert(*k);
    }

    if (hauptKontaktPos != -1) {
        int counter = 0;
        for (auto& kontakt : kontaktList) {
            if (counter == hauptKontaktPos) {
                d.setHauptkontakt(kontakt);
                break;
            }
            counter++;
        }
        ddao->updateHauptkontakt(d);
    }
}

//Schließt das Fenster
void CreateHauptorganisatorView::onExitBtnClicked()
{
    this->close();
}
