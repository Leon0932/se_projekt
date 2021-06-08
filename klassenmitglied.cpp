#include "klassenmitglied.h"

Klassenmitglied::Klassenmitglied()
{

}

Klassenmitglied::Klassenmitglied(int id)
{
    this->id = id;
}

int Klassenmitglied::getId()
{
    return this->id;
}

void Klassenmitglied::setId(int id)
{
    this->id = id;
}
