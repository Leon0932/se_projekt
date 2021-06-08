#ifndef KLASSENMITGLIEDDAO_H
#define KLASSENMITGLIEDDAO_H

#include "klassenmitglied.h"

class KlassenmitgliedDAO
{
public:
    virtual ~KlassenmitgliedDAO() {}
    virtual bool insert(Klassenmitglied &km) = 0;
    virtual bool remove(Klassenmitglied &km) = 0;
    virtual bool clean() = 0;
};

#endif // KLASSENMITGLIEDDAO_H
