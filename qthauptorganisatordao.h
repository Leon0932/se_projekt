#ifndef QTHAUPTORGANISATORDAO_H
#define QTHAUPTORGANISATORDAO_H

#include <QtSql>

#include "hauptorganisatordao.h"

class QtHauptorganisatorDAO : public HauptorganisatorDAO
{
private:
    QSqlQuery insert_qeury, search_query, fetch_query;

public:
    QtHauptorganisatorDAO();
    bool insert(Hauptorganisator &hauptorganisator) override;
    bool fetch(Hauptorganisator &hauptorganisator) override;
    bool search(Hauptorganisator &hauptorganisator) override;
};

#endif // QTHAUPTORGANISATORDAO_H
