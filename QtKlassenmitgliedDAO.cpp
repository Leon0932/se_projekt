#include <QString>

#include "qtklassenmitglieddao.h"

QtKlassenmitgliedDAO::QtKlassenmitgliedDAO()
{
    insert_query.prepare("INSERT INTO Klassenmitglied DEFAULT VALUES;");
}

bool QtKlassenmitgliedDAO::insert(Klassenmitglied &km)
{
    if (!insert_query.exec()) {
        return false;
    }
    km.setId(insert_query.lastInsertId().toInt());
    return true;
}
