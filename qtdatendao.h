#ifndef QTDATENDAO_H
#define QTDATENDAO_H

#include <QtSql>

#include "datendao.h"

class QtDatenDAO : public DatenDAO
{
private:
    //DML = insert, update
    //DQL = search, select, select
    QSqlQuery insert_query, updateHK_query, search_query, select_newest_query, search_email_query, select_query;

public:
    //class definition
    QtDatenDAO();
    //insert Daten
    bool insert(Daten &daten) override;
    //update Daten
    bool update(Daten &daten) override;
    //update Daten
    bool updateHauptkontakt(Daten &daten) override;
    //search daten, list
    bool search(Daten &daten, std::list<Daten*> &datenList) override;
    //search email
    bool searchEmail(Daten &daten) override;
    //select daten
    bool select_newest(Daten &daten) override;
    //select daten, list
    bool select(Daten &daten, std::list<Daten*> *datenList) override;
};

#endif // QTDATENDAO_H
