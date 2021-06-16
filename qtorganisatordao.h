#ifndef QTORGANISATORDAO_H
#define QTORGANISATORDAO_H

#include <QtSql>

#include "organisatordao.h"

class QtOrganisatorDAO : public OrganisatorDAO
{
private:
    //DML = Insert, Update, Remove, Search
    QSqlQuery insert_query, update_query, remove_query, search_query;
public:
    //class definition
    QtOrganisatorDAO();
    //insert organisator
    bool insert(Organisator &organisator) override;
    //update given organisator
    bool update(Organisator &organisator) override;
    //remove over id
    bool remove(int id) override;
    //search organisator
    bool search(Organisator &organisator) override;
};

#endif // QTORGANISATORDAO_H
