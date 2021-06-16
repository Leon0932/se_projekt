#ifndef CHANGEPASSWORTVIEW_H
#define CHANGEPASSWORTVIEW_H

#include <QWidget>
#include "qtorganisatordao.h"

namespace Ui {
class ChangePasswortView;
}

//GUI Klasse um das Passwort zu ändern
class ChangePasswortView : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswortView(QWidget *parent = nullptr);
    //Konstruktor bei dem der Organistor, bei dem das Passwort geändert werden kann übergeben wird, und ob die
    //Klassenliste beim schließen angezeigt werden soll
    ChangePasswortView(Organisator &org, bool openKlassenView);
    ~ChangePasswortView();

public slots:
    //QT Slots für Btn Events der GUI
    void onOkBtnClick();
    void onAbbBtnClick();

private:
    Ui::ChangePasswortView *ui;
    //Objekt des Organisators
    Organisator *org;
    //ob die Klassenliste geöffnet werden soll | standardmäßig nein
    bool openKlassenView = false;
};

#endif // CHANGEPASSWORTVIEW_H
