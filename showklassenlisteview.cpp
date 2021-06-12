#include "showklassenlisteview.h"
#include "ui_showklassenlisteview.h"

ShowKlassenlisteView::ShowKlassenlisteView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowKlassenlisteView)
{
    ui->setupUi(this);
}

ShowKlassenlisteView::~ShowKlassenlisteView()
{
    delete ui;
}
