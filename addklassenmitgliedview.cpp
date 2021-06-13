#include "addklassenmitgliedview.h"
#include "ui_addklassenmitgliedview.h"

AddKlassenmitgliedView::AddKlassenmitgliedView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddKlassenmitgliedView)
{
    ui->setupUi(this);
    connect(ui->uebernehmenBtn, SIGNAL(clicked(bool)), this, SLOT(onUebernehmenBtnClicked()));
    connect(ui->abbrechenBtn, SIGNAL(clicked(bool)), this, SLOT(onAbbrechenBtnClicked()));
    connect(ui->ausloggenButton, SIGNAL(clicked(bool)), this, SLOT(onAusloggenBtnClicked()));
}

void AddKlassenmitgliedView::onUebernehmenBtnClicked()
{

}

void AddKlassenmitgliedView::onAbbrechenBtnClicked()
{

}

void AddKlassenmitgliedView::onAusloggenBtnClicked()
{

}

AddKlassenmitgliedView::~AddKlassenmitgliedView()
{
    delete ui;
}
