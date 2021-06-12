#include "addklassenmitgliedview.h"
#include "ui_addklassenmitgliedview.h"

AddKlassenmitgliedView::AddKlassenmitgliedView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddKlassenmitgliedView)
{
    ui->setupUi(this);
}

AddKlassenmitgliedView::~AddKlassenmitgliedView()
{
    delete ui;
}
