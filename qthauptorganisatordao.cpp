#include <QString>

#include "qthauptorganisatordao.h"

QtHauptorganisatorDAO::QtHauptorganisatorDAO()
{
    insert_qeury.prepare("INSERT INTO Hauptorganisator (org_id) VALUES (:org_id);");
    remove_query.prepare("DELETE FROM Hauptorganisator WHERE id = :org_id;");
    fetch_query.prepare("SELECT * FROM Hauptorganisator;");
    clean_query.prepare("DELETE FROM Hauptorganisator");
}

bool QtHauptorganisatorDAO::insert(Hauptorganisator &hauptorganisator)
{
    insert_qeury.bindValue(":org_id", QString::fromStdString(std::to_string(hauptorganisator.getId())));
    if (!insert_qeury.exec()) {
        return false;
    }
    hauptorganisator.setId(insert_qeury.lastInsertId().toInt());
    return true;
}

bool QtHauptorganisatorDAO::remove(Hauptorganisator &hauptorganisator)
{
    remove_query.bindValue(":org_id", QString::fromStdString(std::to_string(hauptorganisator.getId())));
    return remove_query.exec();
}

bool QtHauptorganisatorDAO::fetch(Hauptorganisator &hauptorganisator)
{
    if (!fetch_query.exec()) {
        return false;
    }
    if (!fetch_query.next()) {
        return false;
    }
    hauptorganisator.setId(fetch_query.value(0).toInt());
    return true;
}

bool QtHauptorganisatorDAO::clean()
{
    return clean_query.exec();
}
