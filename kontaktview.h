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
    //Konstruktoren mit der ursprünglichen View, Adresse der Liste und Position
    explicit KontaktView(CreateHauptorganisatorView *baseForm, list<Kontakt*> &kList);
    explicit KontaktView(CreateHauptorganisatorView *baseForm, list<Kontakt*> &kList, int &hkPos);
    explicit KontaktView(AddKlassenmitgliedView *baseForm, list<Kontakt*> &kList);
    explicit KontaktView(AddKlassenmitgliedView *baseForm, list<Kontakt*> &kList, int &hkPos);
    explicit KontaktView(ProfileView *baseForm, list<Kontakt*> &kList);
    explicit KontaktView(ProfileView *baseForm, list<Kontakt*> &kList, int &hkPos);
    ~KontaktView();

public slots:
    //QT Slots für Btn Events der GUI
    void onAddBtnClick();
    void onRemBtnClick();
    void onOkBtnClick();
    void onAbbBtnClick();

private:
    Ui::KontaktView *ui;
    //Views von denen man kommt
    CreateHauptorganisatorView *baseForm;
    AddKlassenmitgliedView *kmForm;
    ProfileView *profileView;
    //Zeiger auf Position der Hauptkontakts in der Liste
    int *hauptkontaktPos;
    //Zeiger auf Liste mit Kontakten
    list<Kontakt*> *kList;
    //Funktion um die Hauptkontakt auswahl upzudaten
    void updateComboBox();
};

#endif // KONTAKTVIEW_H
