#include "addklassenmitgliedview.h"
#include "ui_addklassenmitgliedview.h"

#include "showklassenlisteview.h"
#include "kontaktview.h"
#include "loginview.h"
#include "profileview.h"

#include "qtdatendao.h"
#include "qtklassenmitglieddao.h"
#include "qtorganisatordao.h"
#include "qthauptorganisatordao.h"

AddKlassenmitgliedView::AddKlassenmitgliedView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddKlassenmitgliedView)
{
    ui->setupUi(this);
    this->setWindowTitle("SE Projekt Gruppe 10 - Klassenmitglied hinzufügen");
    connect(ui->uebernehmenBtn, SIGNAL(clicked(bool)), this, SLOT(onUebernehmenBtnClicked()));
    connect(ui->abbrechenBtn, SIGNAL(clicked(bool)), this, SLOT(onAbbrechenBtnClicked()));
    connect(ui->ausloggenButton, SIGNAL(clicked(bool)), this, SLOT(onAusloggenBtnClicked()));
    connect(ui->klBtn, SIGNAL(clicked(bool)), this, SLOT(onKlassenlisteBtnClicked()));
    connect(ui->meineDatenBtn, SIGNAL(clicked(bool)), this, SLOT(onMeineDatenBtnClicked()));
    connect(ui->kontakteBtn, SIGNAL(clicked(bool)), this, SLOT(onKontakteBtnClicked()));
}

AddKlassenmitgliedView::AddKlassenmitgliedView(std::string nemail) : AddKlassenmitgliedView()
{
    email = nemail;
    DatenDAO *ddao = new QtDatenDAO;
    Daten d;
    d.setEmail(email);
    ddao->searchEmail(d);
    ui->usernameLbl->setText(QString::fromStdString(d.getName() + " " + d.getNachname()));

    Hauptorganisator h;
    h.setId(d.getId());
    HauptorganisatorDAO *hdao = new QtHauptorganisatorDAO();
    if (hdao->search(h)) {
        ui->rolleLbl->setText("Hauptorganisator");
    }
    else {
        ui->rolleLbl->setText("Organisator");
    }
}

void AddKlassenmitgliedView::onUebernehmenBtnClicked()
{
    Daten d = Daten(ui->nnTbx->text().toStdString(), ui->vnTbx->text().toStdString(), ui->gnTbx->text().toStdString(), ui->hnrTbx->text().toInt(),
                    ui->ortTbx->text().toStdString(), ui->laTbx->text().toStdString(), ui->plzTbx->text().toInt(), ui->strTbx->text().toStdString(),
                    ui->emTbx->text().toStdString(), "");

    Klassenmitglied km = Klassenmitglied();
    KlassenmitgliedDAO *kdao = new QtKlassenmitgliedDAO();
    kdao->insert(km);

    Daten d2 = Daten();
    d2.setEmail(email);
    DatenDAO *ddao = new QtDatenDAO();
    ddao->searchEmail(d2);

    Organisator org = Organisator();
    org.setId(d2.getId());

    d.setKlassenmitglied(&km);
    d.setOrganisator(&org);

    ddao->insert(d);

    KontaktDAO *kodao = new QtKontaktDAO();
    for (auto &kontakt : kontaktList) {
        kontakt->setDaten(&d);
        kodao->insert(*kontakt);
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
        bool update = ddao->updateHauptkontakt(d);
        qDebug() << "update: " << update;
    }

    ShowKlassenlisteView *kv = new ShowKlassenlisteView(this->email);
    kv->show();
    this->close();
}

void AddKlassenmitgliedView::onAbbrechenBtnClicked()
{
    ShowKlassenlisteView *kl = new ShowKlassenlisteView(this->email);
    kl->show();
    this->close();
}

void AddKlassenmitgliedView::onAusloggenBtnClicked()
{
    LoginView *lv = new LoginView();
    lv->show();
    this->close();
}

AddKlassenmitgliedView::~AddKlassenmitgliedView()
{
    delete ui;
}

void AddKlassenmitgliedView::onKontakteBtnClicked()
{
    KontaktView *kv = new KontaktView(this, kontaktList, hauptKontaktPos);
    kv->show();
}

void AddKlassenmitgliedView::onKlassenlisteBtnClicked()
{
    qDebug() << QString::fromStdString(email);
    ShowKlassenlisteView *kl = new ShowKlassenlisteView(email);
    kl->show();
    this->close();
}

void AddKlassenmitgliedView::onMeineDatenBtnClicked()
{
    ProfileView *pv = new ProfileView(email, email);
    pv->setUpdateKlassenliste(false);
    pv->show();
}
