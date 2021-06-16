#ifndef ADDKLASSENMITGLIEDVIEW_H
#define ADDKLASSENMITGLIEDVIEW_H

#include <QMainWindow>
#include <string>
#include <list>
#include "qtkontaktdao.h"

using std::string;

namespace Ui {
class AddKlassenmitgliedView;
}

// GUI Klasse um neues Klassenmitglied hinzuzufügen
class AddKlassenmitgliedView : public QMainWindow
{
    Q_OBJECT

public:
    //Standardkonstruktor der Klasse
    explicit AddKlassenmitgliedView(QWidget *parent = nullptr);
    //Konstruktor mit Email des Organisators um diesen dem Benutzer anzuzeigen
    AddKlassenmitgliedView(string email);
    ~AddKlassenmitgliedView();

public slots:
    //QT Slots für Btn Events der GUI
    void onKontakteBtnClicked();
    void onKlassenlisteBtnClicked();
    void onMeineDatenBtnClicked();
    void onUebernehmenBtnClicked();
    void onAbbrechenBtnClicked();
    void onAusloggenBtnClicked();

private:
    Ui::AddKlassenmitgliedView *ui;
    //email des Organisators
    string email;
    //Liste um die Kontakte, welche man beim erstellen des Klassenmitglieds hinzufügt zu speichern
    std::list<Kontakt*> kontaktList;
    //Position des Hauptkontaktes in der kontaktList
    int hauptKontaktPos = -1;
};

#endif // ADDKLASSENMITGLIEDVIEW_H
