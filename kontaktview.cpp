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
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->addBtn, SIGNAL(clicked(bool)), this, SLOT(onAddBtnClick()));
    connect(ui->remBtn, SIGNAL(clicked(bool)), this, SLOT(onRemBtnClick()));
    connect(ui->okBtn, SIGNAL(clicked(bool)), this, SLOT(onOkBtnClick()));
    connect(ui->abbBtn, SIGNAL(clicked(bool)), this, SLOT(onAbbBtnClick()));
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

