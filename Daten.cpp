#include "daten.h"

const string &Daten::getNachname() const
{
    return nachname;
}

void Daten::setNachname(const string &newNachname)
{
    nachname = newNachname;
}

const string &Daten::getGeburtsname() const
{
    return geburtsname;
}

void Daten::setGeburtsname(const string &newGeburtsname)
{
    geburtsname = newGeburtsname;
}

int Daten::getHausnummer() const
{
    return hausnummer;
}

void Daten::setHausnummer(int newHausnummer)
{
    hausnummer = newHausnummer;
}

const string &Daten::getOrt() const
{
    return ort;
}

void Daten::setOrt(const string &newOrt)
{
    ort = newOrt;
}

const string &Daten::getLand() const
{
    return land;
}

void Daten::setLand(const string &newLand)
{
    land = newLand;
}

int Daten::getPlz() const
{
    return plz;
}

void Daten::setPlz(int newPlz)
{
    plz = newPlz;
}

const string &Daten::getStrasse() const
{
    return strasse;
}

void Daten::setStrasse(const string &newStrasse)
{
    strasse = newStrasse;
}

const string &Daten::getEmail() const
{
    return email;
}

void Daten::setEmail(const string &newEmail)
{
    email = newEmail;
}

const string &Daten::getKommentar() const
{
    return kommentar;
}

void Daten::setKommentar(const string &newKommentar)
{
    kommentar = newKommentar;
}

const string &Daten::getTimestamp() const
{
    return timestamp;
}

void Daten::setTimestamp(const string &newTimestamp)
{
    timestamp = newTimestamp;
}

Kontakt *Daten::getHauptkontakt() const
{
    return hauptkontakt;
}

void Daten::setHauptkontakt(Kontakt *newHauptkontakt)
{
    hauptkontakt = newHauptkontakt;
}

Klassenmitglied *Daten::getKlassenmitglied() const
{
    return klassenmitglied;
}

void Daten::setKlassenmitglied(Klassenmitglied *newKlassenmitglied)
{
    klassenmitglied = newKlassenmitglied;
}

Organisator *Daten::getOrganisator() const
{
    return organisator;
}

void Daten::setOrganisator(Organisator *newOrganisator)
{
    organisator = newOrganisator;
}

const string &Daten::getName() const
{
    return name;
}

void Daten::setName(const string &newName)
{
    name = newName;
}

Daten::Daten()
{

}

//Konstruktor, welcher ein Objekt der Klasse erstellt und die Klassenattribute anhand der Parameter setzt
Daten::Daten(string nachname, string vorname, string geburtsname, int hausnummer, string ort, string land, int plz, string strasse, string email, string kommentar)
{
    this->nachname = nachname;
    this->name = vorname;
    this->geburtsname = geburtsname;
    this->hausnummer = hausnummer;
    this->ort = ort;
    this->land = land;
    this->plz = plz;
    this->strasse = strasse;
    this->email = email;
    this->kommentar = kommentar;
}

Daten::~Daten()
{

}

int Daten::getId() const
{
    return id;
}

void Daten::setId(int newId)
{
    id = newId;
}
