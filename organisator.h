#ifndef ORGANISATOR_H
#define ORGANISATOR_H

#include <string>

#include "klassenmitglied.h"


class Organisator : public Klassenmitglied
{
private:
    std::string password;
public:
    //Konstruktor welcher ein leeres Objekt der Klasse erstellt
    Organisator();
    //Konstruktor, welcher ein Objekt mit gegebene ID und Passwort erstellt
    Organisator(int id, std::string password);
    //Folgende Methoden sind Getter bzw. Setter für das Passwort
    const std::string &getPassword() const;
    void setPassword(const std::string &newPassword);
};

#endif // ORGANISATOR_H
