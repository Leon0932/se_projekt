#ifndef QTHAUPTORGANISATORDAO_H
#define QTHAUPTORGANISATORDAO_H

#include <QtSql>

#include "hauptorganisatordao.h"

class QtHauptorganisatorDAO : public HauptorganisatorDAO
{
private:
    QSqlQuery insert_qeury, remove_query, fetch_query, clean_query;

public:
    QtHauptorganisatorDAO();
    bool insert(Hauptorganisator &hauptorganisator) override;
    bool remove(Hauptorganisator &hauptorganisator) override;
    bool fetch(Hauptorganisator &hauptorganisator) override;
    bool clean() override;
};

#endif // QTHAUPTORGANISATORDAO_H
