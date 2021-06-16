#ifndef QTHAUPTORGANISATORDAO_H
#define QTHAUPTORGANISATORDAO_H

#include <QtSql>

#include "hauptorganisatordao.h"

class QtHauptorganisatorDAO : public HauptorganisatorDAO
{
private:
    //DML = Insert
    //DQL = Search, Fetch
    QSqlQuery insert_query, search_query, fetch_query;

public:
    //class definition
    QtHauptorganisatorDAO();
    //insert hauptorganisator
    bool insert(Hauptorganisator &hauptorganisator) override;
    //fetch hauptorganisator
    bool fetch(Hauptorganisator &hauptorganisator) override;
    //search hauptorganisator
    bool search(Hauptorganisator &hauptorganisator) override;
};

#endif // QTHAUPTORGANISATORDAO_H
