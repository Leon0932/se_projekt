#ifndef HAUPTORGANISATORDAO_H
#define HAUPTORGANISATORDAO_H

#include "hauptorganisator.h"

class HauptorganisatorDAO {
public:
    virtual bool insert(Hauptorganisator &hauptorganisator) = 0;
    virtual bool remove(Hauptorganisator &hauptorganisator) = 0;
    virtual bool search(Hauptorganisator &hauptorganisator) = 0;
    virtual bool fetch(Hauptorganisator &hauptorganisator) = 0;
    virtual bool clean() = 0;
};

#endif // HAUPTORGANISATORDAO_H
