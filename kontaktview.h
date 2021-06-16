#ifndef KONTAKTVIEW_H
#define KONTAKTVIEW_H

#include <QWidget>
#include <list>

#include "createhauptorganisatorview.h"
#include "addklassenmitgliedview.h"
#include "profileview.h"
#include "kontakt.h"

namespace Ui {
class KontaktView;
}

// GUI Klasse um einem Klassenmitglied Kontakte hinzuzufügen
class KontaktView : public QWidget
{
    Q_OBJECT

public:
    explicit KontaktView(QWidget *parent = nullptr);
    //Konstruktoren mit Adresse der Liste und Position
    explicit KontaktView(list<Kontakt*> &kList);
    explicit KontaktView(list<Kontakt*> &kList, int &hkPos);
    ~KontaktView();

public slots:
    //QT Slots für Btn Events der GUI
    void onAddBtnClick();
    void onRemBtnClick();
    void onOkBtnClick();
    void onAbbBtnClick();

private:
    Ui::KontaktView *ui;
    //Zeiger auf Position der Hauptkontakts in der Liste
    int *hauptkontaktPos;
    //Zeiger auf Liste mit Kontakten
    list<Kontakt*> *kList;
    //Funktion um die Hauptkontakt auswahl upzudaten
    void updateComboBox();
};

#endif // KONTAKTVIEW_H
