#ifndef QTDATENDAO_H
#define QTDATENDAO_H

#include <QtSql>

#include "datendao.h"

class QtDatenDAO : public DatenDAO
{
private:
    QSqlQuery insert_query, updateHK_query, search_query, select_newest_query, search_email_query, select_query;

public:
    QtDatenDAO();
    bool insert(Daten &daten) override;
    bool update(Daten &daten) override;
    bool updateHauptkontakt(Daten &daten) override;
    bool search(Daten &daten, std::list<Daten*> &datenList) override;
    bool searchEmail(Daten &daten) override;
    bool select_newest(Daten &daten) override;
    bool select(Daten &daten, std::list<Daten*> *datenList) override;
};

#endif // QTDATENDAO_H
