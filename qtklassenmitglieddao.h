#ifndef QTKLASSENMITGLIEDDAO_H
#define QTKLASSENMITGLIEDDAO_H

#include <QtSql>

#include "klassenmitglieddao.h"

class QtKlassenmitgliedDAO : public KlassenmitgliedDAO
{
private:
    QSqlQuery insert_query;

public:
    QtKlassenmitgliedDAO();
    bool insert(Klassenmitglied &km) override;
};

#endif // QTKLASSENMITGLIEDDAO_H
