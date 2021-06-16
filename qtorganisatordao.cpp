#include "qtorganisatordao.h"
#include <QString>

QtOrganisatorDAO::QtOrganisatorDAO()
{
    //prepared SQL Statements to Insert, Update, Delete and Select
    insert_query.prepare("INSERT INTO Organisator (km_id) VALUES (:km_id)");
    update_query.prepare("UPDATE Organisator SET passwort=:password WHERE km_id=:km_id");
    remove_query.prepare("DELETE FROM Organisator WHERE km_id=:km_id");
    search_query.prepare("SELECT passwort from Organisator WHERE km_id=:km_id");
}

bool QtOrganisatorDAO::insert(Organisator &organisator)
{
    //get organisator id and bind to ":km_id"
    insert_query.bindValue(":km_id", organisator.getId());
    //execute query
    if (!insert_query.exec()) {
        return false;
    }
    //bind organisator password to ":password"
    organisator.setPassword("password");
    return true;
}

bool QtOrganisatorDAO::update(Organisator &organisator)
{
    //get organisator id and bind to ":km_id"
    update_query.bindValue(":km_id", organisator.getId());
    //get organisator password and bind to ":password"
    update_query.bindValue(":password", QString::fromStdString(organisator.getPassword()));
    //execute query
    return update_query.exec();
}

bool QtOrganisatorDAO::remove(int id)
{
    //bind id to ":km_id"
    remove_query.bindValue(":km_id", id);
    //execute query
    return remove_query.exec();
}

bool QtOrganisatorDAO::search(Organisator &organisator)
{
    //get organisator id and set to ":km_id" to search
    search_query.bindValue(":km_id", organisator.getId());
    //execute query
    if (!search_query.exec()) {
        return false;
    }
    //execute next query
    if (!search_query.next()) {
        return false;
    }
    //set organisator password
    organisator.setPassword(search_query.value(0).toString().toStdString());
    return true;
}
