#ifndef HAUPTORGANISATOR_H
#define HAUPTORGANISATOR_H

#include "organisator.h"
#include <string>


class Hauptorganisator: public Organisator
{
public:
    Hauptorganisator();
    Hauptorganisator(int id, std::string password);
};

#endif // HAUPTORGANISATOR_H
