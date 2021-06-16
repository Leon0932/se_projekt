#ifndef KONTAKTDAO_H
#define KONTAKTDAO_H

#include <list>

#include "kontakt.h"

class KontaktDAO {
public:
    virtual bool insert(Kontakt &kontakt) = 0;
    virtual bool update(Kontakt &kontakt) = 0;
    virtual bool search(Kontakt &kontakt) = 0;
    virtual bool select(Kontakt &kontakt, std::list<Kontakt*> &kontaktList) = 0;
};

#endif // KONTAKTDAO_H
