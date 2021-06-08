#include <QString>

#include "qtklassenmitglieddao.h"

QtKlassenmitgliedDAO::QtKlassenmitgliedDAO()
{
    insert_query.prepare("INSERT INTO Klassenmitglied DEFAULT VALUES;");
    remove_query.prepare("DELETE FROM Klassenmitglied WHERE id = :id;");
    clean_query.prepare("DELETE FROM Klassenmitglied");
}

bool QtKlassenmitgliedDAO::insert(Klassenmitglied &km)
{
    if (!insert_query.exec()) {
        return false;
    }
    km.setId(insert_query.lastInsertId().toInt());
    return true;
}

bool QtKlassenmitgliedDAO::remove(Klassenmitglied &km)
{
    QString id = QString::fromStdString(std::to_string(km.getId()));
    remove_query.bindValue(":id", id);
    return remove_query.exec();
}

bool QtKlassenmitgliedDAO::clean()
{
    return clean_query.exec();
}
