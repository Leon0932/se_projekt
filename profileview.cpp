#include "profileview.h"
#include "ui_profileview.h"

#include "qtdatendao.h"

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
}

ProfileView::ProfileView(std::string email) : ProfileView()
{
    DatenDAO *ddao = new QtDatenDAO();
    Daten d;
    d.setEmail(email);
    ddao->searchEmail(d);

    ddao->search(d, this->datenList);
    initTbx(0);
}

ProfileView::~ProfileView()
{
    delete ui;
}

void ProfileView::onOkBtnClick()
{
    qDebug() << "Click";
}

void ProfileView::onuebernehmenBtnClick()
{

}

void ProfileView::abbBtnClick()
{

}

void ProfileView::pwAendernBtnClick()
{

}

void ProfileView::orgRechteBtnClick()
{

}

void ProfileView::kontakteBtnClick()
{

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

            return;
        }
    }
}
