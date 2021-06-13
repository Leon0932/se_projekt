#include "createhauptorganisatorview.h"
#include "ui_createhauptorganisatorview.h"

#include "datendao.h"
#include "qtdatendao.h"

#include "hauptorganisatordao.h"
#include "qthauptorganisatordao.h"
#include "hauptorganisator.h"

#include "klassenmitglieddao.h"
#include "qtklassenmitglieddao.h"

#include "loginview.h"
#include "organisatordao.h"
#include "qtorganisatordao.h"

#include <iostream>
#include <string>
using std::string;

CreateHauptorganisatorView::CreateHauptorganisatorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateHauptorganisatorView)
{
    ui->setupUi(this);
    connect(ui->kontakteBtn, SIGNAL(clicked(bool)), this, SLOT(onKontakteBtnClicked()));
    connect(ui->saveBtn, SIGNAL(clicked(bool)), this, SLOT(onSaveBtnClicked()));
    connect(ui->exitBtn, SIGNAL(clicked(bool)), this, SLOT(onExitBtnClicked()));
}

CreateHauptorganisatorView::~CreateHauptorganisatorView()
{
    delete ui;
}

void CreateHauptorganisatorView::onKontakteBtnClicked()
{

}

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
}

void CreateHauptorganisatorView::onExitBtnClicked()
{
    this->close();
}
