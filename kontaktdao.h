#ifndef KONTAKTDAO_H
#define KONTAKTDAO_H

#include <list>

#include "kontakt.h"

class KontaktDAO {
public:
    //interface insert kontakt
    virtual bool insert(Kontakt &kontakt) = 0;
    //interface update kontakt
    virtual bool update(Kontakt &kontakt) = 0;
    //interface serach kontakt
    virtual bool search(Kontakt &kontakt) = 0;
    //interface select kontakt, list
    virtual bool select(Kontakt &kontakt, std::list<Kontakt*> &kontaktList) = 0;
};

#endif // KONTAKTDAO_H
