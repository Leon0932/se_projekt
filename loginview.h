#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

#include "daten.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginView; }
QT_END_NAMESPACE

// GUI Klasse um sich einzuloggen
class LoginView : public QWidget
{
    Q_OBJECT

public:
    LoginView(QWidget *parent = nullptr);
    //Konstruktor der einen Zeiger auf ein Datenobjekt nimmt
    LoginView(Daten &d);
    ~LoginView();

public slots:
    //QT Slots für Btn Events der GUI
    void onLoginBtnClicked();
    void onExitBtnClicked();

private:
    Ui::LoginView *ui;
    //Datenobjekt
    Daten d;
    //Versuche um sich einzuloggen
    int attempts = 0;
};
#endif // LOGINVIEW_H
