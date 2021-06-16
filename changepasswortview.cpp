#include "changepasswortview.h"
#include "ui_changepasswortview.h"
#include "loginview.h"
#include "showklassenlisteview.h"
#include "qtdatendao.h"

#include "QMessageBox"

//Hauptkonstruktor welcher den Titel des Fensters setzt und die Signals der Buttons mit den Slots verbindet
ChangePasswortView::ChangePasswortView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswortView)
{
    ui->setupUi(this);
    this->setWindowTitle("SE Projekt Gruppe 10 - Passwort ändern");
    connect(ui->okBtn, SIGNAL(clicked(bool)), this, SLOT(onOkBtnClick()));
    connect(ui->cancelBtn, SIGNAL(clicked(bool)), this, SLOT(onAbbBtnClick()));
}

//Konstruktor der den Organisator und ob die Klassenliste gezeigt werden soll setzt
ChangePasswortView::ChangePasswortView(Organisator &org, bool openKlassenView) : ChangePasswortView()
{
    this->org = &org;
    this->openKlassenView = openKlassenView;
}

ChangePasswortView::~ChangePasswortView()
{
    delete ui;
}

//prüft ob passwort gleich sind, nicht standardpasswort und vorhanden
//wenn ja wird das passwort in der Datenbank upgedatet
void ChangePasswortView::onOkBtnClick()
{
    string newPw = ui->newPwTbx->text().toStdString();
    string wdpPw = ui->wdPwTbx->text().toStdString();

    if (newPw.empty() || wdpPw.empty()) {
        QMessageBox *box = new QMessageBox();
        box->setIcon(QMessageBox::Critical);
        box->setText("Passwort eingeben!");
        box->show();
        return;
    }

    if (newPw.compare("password") == 0) {
        QMessageBox *box = new QMessageBox();
        box->setIcon(QMessageBox::Critical);
        box->setText("passwort kann nicht standardpasswort sein!");
        box->show();
        return;
    }
    if (newPw.compare(wdpPw) != 0) {
        QMessageBox *box = new QMessageBox();
        box->setIcon(QMessageBox::Critical);
        box->setText("Passwörter sind nicht gleich");
        box->show();
        return;
    }
    OrganisatorDAO *odao = new QtOrganisatorDAO();
    this->org->setPassword(newPw);
    if (!odao->update(*org)) {
        QMessageBox *box = new QMessageBox();
        box->setIcon(QMessageBox::Critical);
        box->setText("Passwort konnte nicht geändert werden");
        box->show();
    }

    if (this->openKlassenView) {
        DatenDAO *ddao = new QtDatenDAO();
        Daten d;
        d.setKlassenmitglied(this->org);
        ddao->select_newest(d);
        ShowKlassenlisteView *kv = new ShowKlassenlisteView(d.getEmail());
        kv->show();
    }
    this->close();
}

//schließt das Fenster
void ChangePasswortView::onAbbBtnClick()
{
    this->close();
}
