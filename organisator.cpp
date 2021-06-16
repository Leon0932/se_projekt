#include "organisator.h"


const std::string &Organisator::getPassword() const
{
    return password;
}

void Organisator::setPassword(const std::string &newPassword)
{
    password = newPassword;
}

Organisator::Organisator()
{

}

//Erstellt Objekt von Organisator und setzt das Passwort anhand des Parameters
Organisator::Organisator(int id, std::string password) : Klassenmitglied(id)
{
    this->password = password;
}
