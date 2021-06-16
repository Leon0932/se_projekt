#ifndef QTKLASSENMITGLIEDDAO_H
#define QTKLASSENMITGLIEDDAO_H

#include <QtSql>

#include "klassenmitglieddao.h"

class QtKlassenmitgliedDAO : public KlassenmitgliedDAO
{
private:
    //create insert
    QSqlQuery insert_query;

public:
    //class definition
    QtKlassenmitgliedDAO();
    //insert klassenmitglied
    bool insert(Klassenmitglied &km) override;
};

#endif // QTKLASSENMITGLIEDDAO_H
