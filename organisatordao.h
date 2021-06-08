#ifndef ORGANISATORDAO_H
#define ORGANISATORDAO_H

#include <list>

#include "organisator.h"

class OrganisatorDAO {
public:
    virtual bool insert(Organisator &organisator) = 0;
    virtual bool update(Organisator &organisator) = 0;
    virtual bool remove(int id) = 0;
    virtual bool search(Organisator &organisator) = 0;
    virtual bool clean() = 0;
};

#endif // ORGANISATORDAO_H
