#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include <QWidget>

#include <string>
#include "daten.h"
#include <list>
#include "qtorganisatordao.h"
#include "qtklassenmitglieddao.h"
#include "showklassenlisteview.h"

namespace Ui {
class ProfileView;
}

// GUI Klasse um das Profil/Änderungshistorie anzuzeigen
class ProfileView : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileView(QWidget *parent = nullptr);
    //Konstruktor mit email des Klassenmitglieds, und des Organisators, welcher dieses Profil öffnet
    ProfileView(std::string kmEmail, std::string orgEmail);
    ~ProfileView();
    //Fügt die KlassenlistView hinzu um diese upzudaten
    void addKlassenlistView(ShowKlassenlisteView *kv);
    //lädt die Daten des Klassenmitglieds
    void loadData();
    //checkt, welche Aktionen der Organisator durchführen darf
    void checkPermissions();
    void setUpdateKlassenliste(bool newUpdateKlassenliste);

public slots:
    //QT Slots für Btn Events der GUI
    void onOkBtnClick();
    void onuebernehmenBtnClick();
    void abbBtnClick();
    void pwAendernBtnClick();
    void orgRechteBtnClick();
    void kontakteBtnClick();
    void onPrevBtnClick();
    void onNextBtnClick();

private:
    Ui::ProfileView *ui;
    //Liste mit allen Daten eines Klassenmitglieds
    std::list<Daten*> datenList;
    //Liste mit den Kontaktdaten der Daten eines Klassenmitglieds
    std::list<Kontakt*> kontaktList;
    std::string kmEmail;
    std::string orgEmail;
    //Position des Hauptkontakts in der kontaktList
    int hauptKontaktPos = -1;
    //Der Organisator, welcher das Fenster öffnet
    Organisator org;
    //Das Klassenmitglieds, welches angeschaut wird
    Klassenmitglied km;
    //Referenz auf die KlassenlisteView
    ShowKlassenlisteView *kv;
    //Position in der Änderungshistorie
    int listPos;
    //setzt die Textboxen auf das aktuelle
    void initTbx(int listPos);
    //überprüft ob die KLassenliste upgedatet werden soll
    bool updateKlassenliste = true;
};

#endif // PROFILEVIEW_H
