#include <QString>

#include "qtklassenmitglieddao.h"

QtKlassenmitgliedDAO::QtKlassenmitgliedDAO()
{
    //prepared SQL Statements to Insert
    insert_query.prepare("INSERT INTO Klassenmitglied DEFAULT VALUES;");
}

bool QtKlassenmitgliedDAO::insert(Klassenmitglied &km)
{
    //execute query
    if (!insert_query.exec()) {
        return false;
    }
    //set id of last Inserted ID
    km.setId(insert_query.lastInsertId().toInt());
    return true;
}
