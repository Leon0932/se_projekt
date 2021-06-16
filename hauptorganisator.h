#ifndef HAUPTORGANISATOR_H
#define HAUPTORGANISATOR_H

#include "organisator.h"
#include <string>


class Hauptorganisator: public Organisator
{
public:
    //Konstruktor, welcher leeres Objekt erstellt
    Hauptorganisator();
    //Konstruktor, welcher ein Objekt mit eine ID sowie ein Passwort erstellt
    Hauptorganisator(int id, std::string password);
};

#endif // HAUPTORGANISATOR_H
