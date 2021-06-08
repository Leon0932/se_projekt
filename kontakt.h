#ifndef KONTAKT_H
#define KONTAKT_H

#include <string>

using std::string;

class Daten;

class Kontakt
{
private:
    int id;
    string nummer;
    string vorwahl;
    Daten *daten;

public:
    Kontakt();
    Kontakt(int nummer, int vorwahl, Daten &d);
    Kontakt(int id, int nummer, int vorwahl, Daten &d);
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
