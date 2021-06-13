#include "showklassenlisteview.h"
#include "ui_showklassenlisteview.h"

#include "qtdatendao.h"

#include "QTableWidgetItem"

#include <iostream>
#include <list>
using std::list;

ShowKlassenlisteView::ShowKlassenlisteView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowKlassenlisteView)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(onTablerowClicked(int,int)));
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(onTablerowDoubleClick(int,int)));
    connect(ui->ausloggenButton, SIGNAL(clicked(bool)), this, SLOT(onAusloggenBtnClicked()));
    connect(ui->addKmBtn, SIGNAL(clicked(bool)), this, SLOT(onAddKlassenmitgliedLblClicked()));

    init();
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

    ui->tableWidget->setRowCount(dList->size());
    ui->tableWidget->setColumnCount(2);
    int counter = 0;
    for (auto const& i : *dList) {
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(i->getNachname()));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(i->getEmail()));
        ui->tableWidget->setItem(counter, 0, item);
        ui->tableWidget->setItem(counter, 1, item2);
        counter++;
    }
}

void ShowKlassenlisteView::onTablerowClicked(int row, int col)
{
    std::cout << "Single row:" << row << ", column:" << col << std::endl;
}

void ShowKlassenlisteView::onTablerowDoubleClick(int row, int col)
{
    std::cout << "Double row:" << row << ", column:" << col << std::endl;
}

void ShowKlassenlisteView::onAusloggenBtnClicked()
{
    
}

void ShowKlassenlisteView::onAddKlassenmitgliedLblClicked()
{
    
}

void ShowKlassenlisteView::onShowProfileLblClicked()
{
    
}
