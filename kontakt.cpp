#include "kontakt.h"

int Kontakt::getId() const
{
    return id;
}

void Kontakt::setId(int newId)
{
    id = newId;
}

string Kontakt::getNummer() const
{
    return nummer;
}

void Kontakt::setNummer(string newNummer)
{
    nummer = newNummer;
}

string Kontakt::getVorwahl() const
{
    return vorwahl;
}

void Kontakt::setVorwahl(string newVorwahl)
{
    vorwahl = newVorwahl;
}


Daten *Kontakt::getDaten() const
{
    return daten;
}

void Kontakt::setDaten(Daten *newDaten)
{
    daten = newDaten;
}

Kontakt::Kontakt()
{

}

Kontakt::Kontakt(int nummer, int vorwahl, Daten &d)
{
    this->nummer = nummer;
    this->vorwahl = vorwahl;
    this->daten = &d;
}

Kontakt::Kontakt(int id, int nummer, int vorwahl, Daten &d)
{
    this->id = id;
    this->nummer = nummer;
    this->vorwahl = vorwahl;
    this->daten = &d;
}
