#ifndef KLASSENMITGLIEDDAO_H
#define KLASSENMITGLIEDDAO_H

#include "klassenmitglied.h"

class KlassenmitgliedDAO
{
public:
    //destructor for class
    virtual ~KlassenmitgliedDAO() {}
    //interface insert reference to km
    virtual bool insert(Klassenmitglied &km) = 0;
};

#endif // KLASSENMITGLIEDDAO_H
