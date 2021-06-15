#include "profileview.h"
#include "ui_profileview.h"

#include "qtdatendao.h"
#include "qtkontaktdao.h"
#include "qthauptorganisatordao.h"
#include "kontaktview.h"
#include "changepasswortview.h"

#include "QMessageBox"

ProfileView::ProfileView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileView)
{
    ui->setupUi(this);
    this->setWindowTitle("SE Projekt Gruppe 10 - Profil");
    connect(ui->okBtn, SIGNAL(clicked(bool)), this, SLOT(onOkBtnClick()));
    connect(ui->uebernehmenBtn, SIGNAL(clicked(bool)), this, SLOT(onuebernehmenBtnClick()));
    connect(ui->abbBtn, SIGNAL(clicked(bool)), this, SLOT(abbBtnClick()));
    connect(ui->pwAendernBtn, SIGNAL(clicked(bool)), this, SLOT(pwAendernBtnClick()));
    connect(ui->orgRechteBtn, SIGNAL(clicked(bool)), this, SLOT(orgRechteBtnClick()));
    connect(ui->kontakteBtn, SIGNAL(clicked(bool)), this, SLOT(kontakteBtnClick()));
    connect(ui->nextBtn, SIGNAL(clicked(bool)), this, SLOT(onNextBtnClick()));
    connect(ui->prevBtn, SIGNAL(clicked(bool)), this, SLOT(onPrevBtnClick()));
}

ProfileView::ProfileView(std::string kmEmail, std::string orgEmail) : ProfileView()
{
    this->kmEmail = kmEmail;
    this->orgEmail = orgEmail;
    loadData();
    checkPermissions();
}

ProfileView::~ProfileView()
{
    delete ui;
}

void ProfileView::addKlassenlistView(ShowKlassenlisteView *kv)
{
    this->kv = kv;
}

void ProfileView::loadData()
{
    this->datenList.clear();

    DatenDAO *ddao = new QtDatenDAO();
    OrganisatorDAO *odao = new QtOrganisatorDAO();

    Daten orgDaten;
    orgDaten.setEmail(orgEmail);
    ddao->searchEmail(orgDaten);

    this->org.setId(orgDaten.getId());
    odao->search(this->org);

    Daten d;
    d.setEmail(kmEmail);
    ddao->searchEmail(d);
    this->km.setId(d.getKlassenmitglied()->getId());

    ddao->search(d, this->datenList);
    this->listPos = datenList.size() - 1;
    initTbx(this->listPos);

    ui->maxPosLbl->setText(QString::number(this->datenList.size()));
    ui->curPosLbl->setText(QString::number(this->listPos + 1));
}

void ProfileView::checkPermissions()
{
    Hauptorganisator hauptorganisator;
    hauptorganisator.setId(org.getId());
    HauptorganisatorDAO *hdao = new QtHauptorganisatorDAO();
    if (hdao->search(hauptorganisator)) {
        //hat alle Rechte
        return;
    }

    Organisator organisator;
    organisator.setId(km.getId());
    OrganisatorDAO *odao = new QtOrganisatorDAO();
    if (odao->search(organisator) && (org.getId() != km.getId())) {
        //km ist Organisator und Organisator nicht Hauptorganisator
        ui->kontakteBtn->setEnabled(false);
        ui->orgRechteBtn->setEnabled(false);
        ui->pwAendernBtn->setEnabled(false);
        ui->okBtn->setEnabled(false);
        ui->uebernehmenBtn->setEnabled(false);

        ui->nachnameTbx->setReadOnly(true);
        ui->vornameTbx->setReadOnly(true);
        ui->geburtsnameTbx->setReadOnly(true);
        ui->emailTbx->setReadOnly(true);
        ui->landTbx->setReadOnly(true);
        ui->plzTbx->setReadOnly(true);
        ui->ortTbx->setReadOnly(true);
        ui->strasseTbx->setReadOnly(true);
        ui->hausnummerTbx->setReadOnly(true);
        ui->kommentarTbx->setReadOnly(true);
    }
}

void ProfileView::onOkBtnClick()
{
    onuebernehmenBtnClick();
    this->close();
}

void ProfileView::onuebernehmenBtnClick()
{
    if (ui->emailTbx->text().isEmpty()) {
        QMessageBox *box = new QMessageBox();
        box->setIcon(QMessageBox::Critical);
        box->setWindowTitle("FEHLER");
        box->setText("Email Adresse darf nicht leer sein");
        box->show();
        return;
    }

    Daten d = Daten(ui->nachnameTbx->text().toStdString(), ui->vornameTbx->text().toStdString(), ui->geburtsnameTbx->text().toStdString(),
                    ui->hausnummerTbx->text().toInt(), ui->ortTbx->text().toStdString(), ui->landTbx->text().toStdString(),
                    ui->plzTbx->text().toInt(), ui->strasseTbx->text().toStdString(), ui->emailTbx->text().toStdString(), ui->kommentarTbx->text().toStdString());

    d.setKlassenmitglied(&km);
    d.setOrganisator(&org);

    DatenDAO *ddao = new QtDatenDAO();
    ddao->insert(d);

    KontaktDAO *kdao = new QtKontaktDAO();
    for (auto &kontakt : kontaktList) {
        kontakt->setDaten(&d);
        kdao->insert(*kontakt);
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

    loadData();

    if (updateKlassenliste) {
        kv->init();
    }
}

void ProfileView::abbBtnClick()
{
    this->close();
}

void ProfileView::pwAendernBtnClick()
{
    Organisator *o = new Organisator();
    o->setId(this->km.getId());

    OrganisatorDAO *odao = new QtOrganisatorDAO();
    if (odao->search(*o)) {
        ChangePasswortView *cv = new ChangePasswortView(*o, false);
        cv->show();
    }
}

void ProfileView::orgRechteBtnClick()
{
    qDebug() << "pressed";
    OrganisatorDAO *odao = new QtOrganisatorDAO();
    Organisator o;
    o.setId(km.getId());
    if (odao->search(o)) {
        //ist Organisator
        QMessageBox *box = new QMessageBox();
        box->setIcon(QMessageBox::Information);
        box->setWindowTitle("Info");
        box->setText("Organisatorrechte entzogen");
        box->show();
        odao->remove(km.getId());
    }
    else {
        //ist kein Organisator
        QMessageBox *box = new QMessageBox();
        box->setIcon(QMessageBox::Information);
        box->setWindowTitle("Info");
        box->setText("Organisatorrechte gegeben");
        box->show();
        odao->insert(o);
    }
    checkPermissions();
}

void ProfileView::kontakteBtnClick()
{
    KontaktView *kv = new KontaktView(this, kontaktList, hauptKontaktPos);
    kv->show();
}

void ProfileView::onPrevBtnClick()
{
    if (this->listPos - 1 < 0) {
        return;
    }

    this->listPos -=1;
    ui->curPosLbl->setText(QString::number(this->listPos + 1));
    initTbx(this->listPos);
}

void ProfileView::onNextBtnClick()
{
    int size = datenList.size();
    if (this->listPos + 1 >= size) {
        return;
    }

    this->listPos += 1;
    ui->curPosLbl->setText(QString::number(this->listPos + 1));
    initTbx(this->listPos);
}

void ProfileView::initTbx(int listPos)
{
    int counter = 0;
    for (auto const& daten : datenList) {
        if (counter == listPos) {
            ui->nachnameTbx->setText(QString::fromStdString(daten->getNachname()));
            ui->vornameTbx->setText(QString::fromStdString(daten->getName()));
            ui->geburtsnameTbx->setText(QString::fromStdString(daten->getGeburtsname()));
            ui->emailTbx->setText(QString::fromStdString(daten->getEmail()));
            ui->landTbx->setText(QString::fromStdString(daten->getLand()));
            ui->ortTbx->setText(QString::fromStdString(daten->getOrt()));
            ui->strasseTbx->setText(QString::fromStdString(daten->getStrasse()));
            ui->plzTbx->setText(QString::number(daten->getPlz()));
            ui->hausnummerTbx->setText(QString::number(daten->getHausnummer()));
            ui->kommentarTbx->setText(QString::fromStdString(daten->getKommentar()));

            Daten orgDaten;
            orgDaten.setKlassenmitglied(daten->getOrganisator());
            DatenDAO *ddao = new QtDatenDAO();
            ddao->select_newest(orgDaten);

            ui->orgTbx->setText(QString::fromStdString(orgDaten.getName() + " " + orgDaten.getNachname()));
            ui->hautpkontaktTbx->setText(QString::fromStdString(daten->getHauptkontakt()->getVorwahl() + "/" + daten->getHauptkontakt()->getNummer()));

            Kontakt hk;
            daten->getHauptkontakt();

            this->kontaktList.clear();
            KontaktDAO *kdao = new QtKontaktDAO();
            Kontakt k = Kontakt();
            k.setDaten(daten);
            kdao->select(k, this->kontaktList);
            return;
        }
        counter++;
    }
}

void ProfileView::setUpdateKlassenliste(bool newUpdateKlassenliste)
{
    updateKlassenliste = newUpdateKlassenliste;
}
