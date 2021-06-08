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
    int id;

    Kontakt *hauptkontakt;
    Klassenmitglied *klassenmitglied;
    Organisator *organisator;

public:
    Daten();
    Daten(string nachname, string vorname, string geburtsname, int hausnummer, string ort, string land,
          int plz, string strasse, string email, string kommentar);
    ~Daten();
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
