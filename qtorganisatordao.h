#ifndef QTORGANISATORDAO_H
#define QTORGANISATORDAO_H

#include <QtSql>

#include "organisatordao.h"

class QtOrganisatorDAO : public OrganisatorDAO
{
private:
    QSqlQuery insert_query, update_query, remove_query, search_query, clean_query;
public:
    QtOrganisatorDAO();
    bool insert(Organisator &organisator) override;
    bool update(Organisator &organisator) override;
    bool remove(int id) override;
    bool search(Organisator &organisator) override;
    bool clean() override;
};

#endif // QTORGANISATORDAO_H
