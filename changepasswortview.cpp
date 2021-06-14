#include "changepasswortview.h"
#include "ui_changepasswortview.h"
#include "loginview.h"
#include "showklassenlisteview.h"

ChangePasswortView::ChangePasswortView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswortView)
{
    ui->setupUi(this);
    this->setWindowTitle("SE Projekt Gruppe 10 - Passwort ändern");
    connect(ui->okBtn, SIGNAL(clicked(bool)), this, SLOT(onOkBtnClick()));
    connect(ui->cancelBtn, SIGNAL(clicked(bool)), this, SLOT(onAbbBtnClick()));
}

ChangePasswortView::ChangePasswortView(Organisator &org, bool openKlassenView) : ChangePasswortView()
{
    this->org = &org;
    this->openKlassenView = openKlassenView;
}

ChangePasswortView::~ChangePasswortView()
{
    delete ui;
}

void ChangePasswortView::onOkBtnClick()
{
    string newPw = ui->newPwTbx->text().toStdString();
    string wdpPw = ui->wdPwTbx->text().toStdString();

    if (newPw.compare("password") == 0) {
        qDebug() << "password kann nicht pw sein";
        return;
    }
    if (newPw.compare(wdpPw) != 0) {
        qDebug() << "passwörter sind nicht gleich";
        return;
    }
    OrganisatorDAO *odao = new QtOrganisatorDAO();
    this->org->setPassword(newPw);
    if (!odao->update(*org)) {
        qDebug() << "password nicht geändert";
    }

    if (this->openKlassenView) {
        ShowKlassenlisteView *kv = new ShowKlassenlisteView();
        kv->show();
    }
    this->close();
}

void ChangePasswortView::onAbbBtnClick()
{
    LoginView *lv = new LoginView();
    lv->show();
    this->close();
}
