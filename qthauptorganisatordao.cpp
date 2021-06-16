#include <QString>

#include "qthauptorganisatordao.h"

QtHauptorganisatorDAO::QtHauptorganisatorDAO()
{
    //prepared SQL Statements to Insert and Select
    insert_query.prepare("INSERT INTO Hauptorganisator (org_id) VALUES (:org_id);");
    search_query.prepare("SELECT * FROM Hauptorganisator WHERE org_id=:org_id");
    fetch_query.prepare("SELECT * FROM Hauptorganisator;");
}

bool QtHauptorganisatorDAO::insert(Hauptorganisator &hauptorganisator)
{
    //bind id to ":ord_id" to prepared insert query
    insert_query.bindValue(":org_id", QString::fromStdString(std::to_string(hauptorganisator.getId())));
    //execute query
    if (!insert_query.exec()) {
        return false;
    }

    //set id of last Inserted ID to hauptorganisator id
    hauptorganisator.setId(insert_query.lastInsertId().toInt());
    return true;
}

bool QtHauptorganisatorDAO::fetch(Hauptorganisator &hauptorganisator)
{
    //execute query
    if (!fetch_query.exec()) {
        return false;
    }
    //execute query
    if (!fetch_query.next()) {
        return false;
    }
    //fetch id to set hauptorganisator id
    hauptorganisator.setId(fetch_query.value(0).toInt());
    return true;
}

bool QtHauptorganisatorDAO::search(Hauptorganisator &hauptorganisator)
{
    //bind hauptorganisator id to ":org_id" to prepared search query
    search_query.bindValue(":org_id", hauptorganisator.getId());

    //execute query
    if (!search_query.exec()) {
        return false;
    }
    //execute query
    return search_query.next();
}
