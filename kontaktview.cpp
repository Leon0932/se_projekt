#include "kontaktview.h"
#include "ui_kontaktview.h"

#include <QDebug>
#include <string>
using std::string;

KontaktView::KontaktView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KontaktView)
{
    ui->setupUi(this);
    this->setWindowTitle("SE Projekt Gruppe 10 - Kontakte hinzufügen");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->addBtn, SIGNAL(clicked(bool)), this, SLOT(onAddBtnClick()));
    connect(ui->remBtn, SIGNAL(clicked(bool)), this, SLOT(onRemBtnClick()));
    connect(ui->okBtn, SIGNAL(clicked(bool)), this, SLOT(onOkBtnClick()));
    connect(ui->abbBtn, SIGNAL(clicked(bool)), this, SLOT(onAbbBtnClick()));
}

KontaktView::KontaktView(CreateHauptorganisatorView *baseForm, list<Kontakt*> &kList) : KontaktView()
{
    this->baseForm = baseForm;
    ui->tableWidget->setRowCount(kList.size());
    int counter = 0;
    for (auto const& kontakt : kList) {
        QTableWidgetItem *vorwahlItem = new QTableWidgetItem(QString::fromStdString(kontakt->getVorwahl()));
        QTableWidgetItem *nummerItem = new QTableWidgetItem(QString::fromStdString(kontakt->getNummer()));

        ui->tableWidget->setItem(counter, 0, vorwahlItem);
        ui->tableWidget->setItem(counter, 1, nummerItem);
        counter++;
    }
    updateComboBox();
}

KontaktView::KontaktView(AddKlassenmitgliedView *baseForm, list<Kontakt *> &kList) : KontaktView()
{
    this->kmForm = baseForm;
    ui->tableWidget->setRowCount(kList.size());
    int counter = 0;
    for (auto const& kontakt : kList) {
        QTableWidgetItem *vorwahlItem = new QTableWidgetItem(QString::fromStdString(kontakt->getVorwahl()));
        QTableWidgetItem *nummerItem = new QTableWidgetItem(QString::fromStdString(kontakt->getNummer()));

        ui->tableWidget->setItem(counter, 0, vorwahlItem);
        ui->tableWidget->setItem(counter, 1, nummerItem);
        counter++;
    }
    updateComboBox();
}

KontaktView::KontaktView(ProfileView *baseForm, list<Kontakt *> &kList) : KontaktView()
{
    this->profileView = baseForm;
    this->kList = &kList;
    ui->tableWidget->setRowCount(kList.size());
    int counter = 0;
    for (auto const& kontakt : kList) {
        QTableWidgetItem *vorwahlItem = new QTableWidgetItem(QString::fromStdString(kontakt->getVorwahl()));
        QTableWidgetItem *nummerItem = new QTableWidgetItem(QString::fromStdString(kontakt->getNummer()));

        ui->tableWidget->setItem(counter, 0, vorwahlItem);
        ui->tableWidget->setItem(counter, 1, nummerItem);
        counter++;
    }
    updateComboBox();
}

KontaktView::~KontaktView()
{
    delete ui;
}

void KontaktView::onAddBtnClick()
{
    string vorwahl = ui->vorwahlTbx->text().toStdString();
    string nummer = ui->nummerTbx->text().toStdString();

    if (vorwahl.empty() || nummer.empty()) {
        return;
    }

    int rows = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(rows + 1);

    QTableWidgetItem *vorwahlItem = new QTableWidgetItem(ui->vorwahlTbx->text());
    QTableWidgetItem *nummerItem = new QTableWidgetItem(ui->nummerTbx->text());

    ui->tableWidget->setItem(rows, 0, vorwahlItem);
    ui->tableWidget->setItem(rows, 1, nummerItem);

    updateComboBox();
}

void KontaktView::onRemBtnClick()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();

    if (!select->hasSelection()) {
        return;
    }
    QModelIndex selectedRow = select->selectedRows().at(0);
    qDebug() << selectedRow;
    ui->tableWidget->removeRow(selectedRow.row());

    updateComboBox();
}

void KontaktView::onOkBtnClick()
{
    this->kList->clear();
    int rows = ui->tableWidget->rowCount();
    for (int i = 0; i < rows; i++) {
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);
        string vorwahl = item->text().toStdString();
        QTableWidgetItem *item2 = ui->tableWidget->item(i, 1);
        string nummer = item2->text().toStdString();

        Kontakt *k = new Kontakt();
        k->setVorwahl(vorwahl);
        k->setNummer(nummer);
        this->kList->push_back(k);
    }
    this->close();
}

void KontaktView::onAbbBtnClick()
{
    this->close();
}

void KontaktView::updateComboBox()
{
    ui->comboBox->clear();
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        ui->comboBox->addItem(QString::number(row + 1));
    }
}

