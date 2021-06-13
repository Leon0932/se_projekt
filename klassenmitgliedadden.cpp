#include "klassenmitgliedadden.h"
#include "ui_klassenmitgliedadden.h"

klassenmitgliedAdden::klassenmitgliedAdden(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::klassenmitgliedAdden)
{
    ui->setupUi(this);
}

klassenmitgliedAdden::~klassenmitgliedAdden()
{
    delete ui;
}
