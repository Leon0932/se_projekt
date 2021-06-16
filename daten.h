#ifndef DATEN_H
#define DATEN_H

#include <string>

#include "kontakt.h"
#include "klassenmitglied.h"
#include "organisator.h"

using namespace std;

class Daten
{
private:
    //Personbezogene Daten
    string nachname;
    string name;
    string geburtsname;
    int hausnummer;
    string ort;
    string land;
    int plz;
    string strasse;
    string email;
    string kommentar;
    string timestamp;
    int id;    //Person-ID

    Kontakt *hauptkontakt;      //Definition von Kontakt-Objekt
    Klassenmitglied *klassenmitglied;   //Definition von Klassenmitglied-Objekt
    Organisator *organisator;       //Definition von Organisator-Objekt

public:
    Daten();        //Konstruktor, welcher ein leeres Objekt erstellt
    //Konstruktor der Klasse Daten mit allen personbezogenen Informationen
    Daten(string nachname, string vorname, string geburtsname, int hausnummer, string ort, string land,
          int plz, string strasse, string email, string kommentar);
    ~Daten();       //Dekonstruktor
    //Folgende Methoden sind alle Getter bzw. Setter-Methoden fÃ¼r alle personenbezogenen Informationen
    int getId() const;
    void setId(int newId);
    const string &getNachname() const;
    void setNachname(const string &newNachname);
    const string &getGeburtsname() const;
    void setGeburtsname(const string &newGeburtsname);
    int getHausnummer() const;
    void setHausnummer(int newHausnummer);
    const string &getOrt() const;
    void setOrt(const string &newOrt);
    const string &getLand() const;
    void setLand(const string &newLand);
    int getPlz() const;
    void setPlz(int newPlz);
    const string &getStrasse() const;
    void setStrasse(const string &newStrasse);
    const string &getEmail() const;
    void setEmail(const string &newEmail);
    const string &getKommentar() const;
    void setKommentar(const string &newKommentar);
    const string &getTimestamp() const;
    void setTimestamp(const string &newTimestamp);
    Kontakt *getHauptkontakt() const;
    void setHauptkontakt(Kontakt *newHauptkontakt);
    Klassenmitglied *getKlassenmitglied() const;
    void setKlassenmitglied(Klassenmitglied *newKlassenmitglied);
    Organisator *getOrganisator() const;
    void setOrganisator(Organisator *newOrganisator);
    const string &getName() const;
    void setName(const string &newName);
};

#endif // DATEN_H
