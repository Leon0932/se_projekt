#include "changepasswortview.h"
#include "ui_changepasswortview.h"

ChangePasswortView::ChangePasswortView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswortView)
{
    ui->setupUi(this);
    this->setWindowTitle("SE Projekt Gruppe 10 - Passwort ändern");
}

ChangePasswortView::~ChangePasswortView()
{
    delete ui;
}
