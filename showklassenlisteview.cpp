#include "showklassenlisteview.h"
#include "ui_showklassenlisteview.h"

#include "loginview.h"
#include "addklassenmitgliedview.h"
#include "qtdatendao.h"
#include "qthauptorganisatordao.h"
#include "profileview.h"

#include "QTableWidgetItem"

#include <iostream>
#include <list>
using std::list;

ShowKlassenlisteView::ShowKlassenlisteView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowKlassenlisteView)
{
    ui->setupUi(this);
    this->setWindowTitle("SE Projekt Gruppe 10 - Klassenliste");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(onTablerowClicked(int,int)));
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(onTablerowDoubleClick(int,int)));
    connect(ui->ausloggenButton, SIGNAL(clicked(bool)), this, SLOT(onAusloggenBtnClicked()));
    connect(ui->addKmBtn, SIGNAL(clicked(bool)), this, SLOT(onAddKlassenmitgliedLblClicked()));
    connect(ui->meineDatenbtn, SIGNAL(clicked(bool)), this, SLOT(onMeineDatenBtnClick()));

    init();
}

ShowKlassenlisteView::ShowKlassenlisteView(string nemail) : ShowKlassenlisteView()
{
    email = nemail;
    //qDebug() << QString::fromStdString(email);
    DatenDAO *ddao = new QtDatenDAO;
    Daten d;
    d.setEmail(email);
    ddao->searchEmail(d);
    ui->usernameLbl->setText(QString::fromStdString(d.getName() + " " + d.getNachname()));

    Hauptorganisator h = Hauptorganisator();
    h.setId(d.getId());
    HauptorganisatorDAO *hdao = new QtHauptorganisatorDAO();
    if (hdao->search(h)) {
        ui->rolleLbl->setText("Hauptorganisator");
    }
    else {
        ui->rolleLbl->setText("Organisator");
    }
}

ShowKlassenlisteView::~ShowKlassenlisteView()
{
    delete ui;
}

void ShowKlassenlisteView::init()
{
    Daten d;
    list<Daten*> *dList = new list<Daten*>;
    DatenDAO *ddao = new QtDatenDAO();
    if (!ddao->select(d, dList)) {
        return;
    }

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(dList->size());
    ui->tableWidget->setColumnCount(10); // passe RowCount An!
    int counter = 0;
    for (auto const& i : *dList) {
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(i->getName()));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(i->getNachname()));
        QTableWidgetItem *item3 = new QTableWidgetItem(QString::fromStdString(i->getGeburtsname()));
        QTableWidgetItem *item4 = new QTableWidgetItem(QString::fromStdString(i->getEmail()));
        QTableWidgetItem *item5 = new QTableWidgetItem(QString::fromStdString(i->getLand()));
        QTableWidgetItem *item6 = new QTableWidgetItem(QString::number(i->getPlz()));
        QTableWidgetItem *item7 = new QTableWidgetItem(QString::fromStdString(i->getOrt()));
        QTableWidgetItem *item8 = new QTableWidgetItem(QString::fromStdString(i->getStrasse()));
        QTableWidgetItem *item9 = new QTableWidgetItem(QString::number(i->getHausnummer()));
        QTableWidgetItem *item10 = new QTableWidgetItem(QString::fromStdString(i->getKommentar()));
        ui->tableWidget->setItem(counter, 0, item);
        ui->tableWidget->setItem(counter, 1, item2);
        ui->tableWidget->setItem(counter, 2, item3);
        ui->tableWidget->setItem(counter, 3, item4);
        ui->tableWidget->setItem(counter, 4, item5);
        ui->tableWidget->setItem(counter, 5, item6);
        ui->tableWidget->setItem(counter, 6, item7);
        ui->tableWidget->setItem(counter, 7, item8);
        ui->tableWidget->setItem(counter, 8, item9);
        ui->tableWidget->setItem(counter, 9, item10);

        counter++;
    }
}

void ShowKlassenlisteView::onTablerowDoubleClick(int row, int col)
{
    string email = ui->tableWidget->item(row, 3)->text().toStdString();
    ProfileView *pv = new ProfileView(email, this->email);
    pv->addKlassenlistView(this);
    pv->show();
}

void ShowKlassenlisteView::onAusloggenBtnClicked()
{
    LoginView *lv = new LoginView();
    lv->show();
    this->close();
}

void ShowKlassenlisteView::onAddKlassenmitgliedLblClicked()
{
    AddKlassenmitgliedView *addView = new AddKlassenmitgliedView(email);
    addView->show();
    this->close();
}

void ShowKlassenlisteView::onMeineDatenBtnClick()
{
    ProfileView *pv = new ProfileView(email, this->email);
    pv->addKlassenlistView(this);
    pv->show();
}
