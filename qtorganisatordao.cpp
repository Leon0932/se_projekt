#include "qtorganisatordao.h"
#include <QString>

QtOrganisatorDAO::QtOrganisatorDAO()
{
    insert_query.prepare("INSERT INTO Organisator (km_id) VALUES (:km_id)");
    update_query.prepare("UPDATE Organisator SET passwort=:password WHERE km_id=:km_id");
    remove_query.prepare("DELETE FROM Organisator WHERE km_id=:id");
    search_query.prepare("SELECT passwort from Organisator WHERE km_id=:id");
    clean_query.prepare("DELETE FROM Organisator");
}

bool QtOrganisatorDAO::insert(Organisator &organisator)
{
    insert_query.bindValue(":km_id", organisator.getId());
    if (!insert_query.exec()) {
        return false;
    }
    organisator.setPassword("password");
    return true;
}

bool QtOrganisatorDAO::update(Organisator &organisator)
{
    update_query.bindValue(":km_id", organisator.getId());
    update_query.bindValue(":password", QString::fromStdString(organisator.getPassword()));
    return update_query.exec();
}

bool QtOrganisatorDAO::remove(int id)
{
    remove_query.bindValue(":km_id", id);
    return remove_query.exec();
}

bool QtOrganisatorDAO::search(Organisator &organisator)
{
    search_query.bindValue(":km_id", QString::fromStdString(organisator.getPassword()));
    if (!search_query.exec()) {
        return false;
    }
    if (!search_query.next()) {
        return false;
    }
    organisator.setPassword(search_query.value(0).toString().toStdString());
    return true;
}

bool QtOrganisatorDAO::clean()
{
    return clean_query.exec();
}

