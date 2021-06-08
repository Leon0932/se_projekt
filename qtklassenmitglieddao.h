#ifndef QTKLASSENMITGLIEDDAO_H
#define QTKLASSENMITGLIEDDAO_H

#include <QtSql>

#include "klassenmitglieddao.h"

class QtKlassenmitgliedDAO : public KlassenmitgliedDAO
{
private:
    QSqlQuery insert_query, remove_query, clean_query;

public:
    QtKlassenmitgliedDAO();
    bool insert(Klassenmitglied &km) override;
    bool remove(Klassenmitglied &km) override;
    bool clean() override;
};

#endif // QTKLASSENMITGLIEDDAO_H
