#ifndef CREATEHAUPTORGANISATORVIEW_H
#define CREATEHAUPTORGANISATORVIEW_H

#include <QWidget>
#include <list>
using std::list;

#include "kontakt.h"

namespace Ui {
class CreateHauptorganisatorView;
}

//GUI Klasse um nach erstem Programmstart den Hauptorganisator anzulegen
class CreateHauptorganisatorView : public QWidget
{
    Q_OBJECT

public:
    explicit CreateHauptorganisatorView(QWidget *parent = nullptr);
    ~CreateHauptorganisatorView();

public slots:
    //QT Slots für Btn Events der GUI
    void onKontakteBtnClicked();
    void onSaveBtnClicked();
    void onExitBtnClicked();

private:
    Ui::CreateHauptorganisatorView *ui;
    //Kontaktliste für den Hauptorganisator
    list<Kontakt*> kontaktList;
    //Position an der der Hauptorganisator steht
    int hauptKontaktPos = -1;
};

#endif // CREATEHAUPTORGANISATORVIEW_H
