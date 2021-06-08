#ifndef ORGANISATOR_H
#define ORGANISATOR_H

#include <string>

#include "klassenmitglied.h"


class Organisator : public Klassenmitglied
{
private:
    std::string password;
public:
    Organisator();
    Organisator(int id, std::string password);
    const std::string &getPassword() const;
    void setPassword(const std::string &newPassword);
};

#endif // ORGANISATOR_H
