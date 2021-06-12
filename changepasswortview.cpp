#include "changepasswortview.h"
#include "ui_changepasswortview.h"

ChangePasswortView::ChangePasswortView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswortView)
{
    ui->setupUi(this);
}

ChangePasswortView::~ChangePasswortView()
{
    delete ui;
}
