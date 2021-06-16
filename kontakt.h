#ifndef KONTAKT_H
#define KONTAKT_H

#include <string>

using std::string;

class Daten;    //Kontakt benötigt personenbezogen Daten, daher kennt Kontakt auch die Klasse Daten

class Kontakt
{
private:
    int id;     //ID des Kontakts
    string nummer;  //Telefonnummer des Kontakts ohne Vorwahl
    string vorwahl; //Vorwahl für die Telefonnummer
    Daten *daten;   //Definition eines Objekts der Klasse Daten

public:
    Kontakt();  //Konstruktor, welcher ein leeres Objekt der Klasse erstellt
    Kontakt(int nummer, int vorwahl, Daten &d);     //Konstruktor, welcher ein Objekt der Klasse erstellt und die Telefonnummer sowie die Daten setzt aber ohne ID
    Kontakt(int id, int nummer, int vorwahl, Daten &d);  //Konstruktor, welcher ein Objekt der Klasse erstellt und die Telefonnummer sowie die Daten setzt mit ID
    //Folgende Methoden sind Getter bzw. Setter für die Attribute der Klasse
    int getId() const;
    void setId(int newId);
    string getNummer() const;
    void setNummer(string newNummer);
    string getVorwahl() const;
    void setVorwahl(string newVorwahl);
    Daten *getDaten() const;
    void setDaten(Daten *newDaten);
};

#endif // KONTAKT_H
