#ifndef QTDATENDAO_H
#define QTDATENDAO_H

#include <QtSql>

#include "datendao.h"

class QtDatenDAO : public DatenDAO
{
private:
    QSqlQuery insert_query, search_query, search_email_query, select_query, clean_query;

public:
    QtDatenDAO();
    bool insert(Daten &daten) override;
    bool update(Daten &daten) override;
    bool remove(int id) override;
    bool search(Daten &daten, std::list<Daten*> &datenList) override;
    bool searchEmail(Daten &daten) override;
    bool select(Daten &daten, std::list<Daten*> *datenList) override;
    bool clean() override;
};

#endif // QTDATENDAO_H
