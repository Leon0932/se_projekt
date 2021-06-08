#ifndef DATENDAO_H
#define DATENDAO_H

#include "daten.h"
#include <list>

class DatenDAO
{
public:
    virtual bool insert(Daten &daten) = 0;
    virtual bool update(Daten &daten) = 0;
    virtual bool remove(int id) = 0;
    virtual bool search(Daten &daten) = 0;
    virtual bool searchEmail(Daten &daten) = 0;
    virtual bool select(Daten &daten, std::list<Kontakt*> datenList) = 0;
    virtual bool clean() = 0;
};

#endif // DATENDAO_H
