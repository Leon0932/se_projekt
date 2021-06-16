#include <QString>

#include "qtkontaktdao.h"
#include "daten.h"

QtKontaktDAO::QtKontaktDAO()
{
    //prepared SQL Statements to Insert, Update and Select
    insert_query.prepare("INSERT INTO Kontakt (nummer, vorwahl, daten_id) VALUES (:nummer, :vorwahl, :daten_id)");
    update_query.prepare("UPDATE Kontakt SET nummer=:nummer, vorwahl=:vorwahl, daten_id=:daten_id WHERE id=:id");
    search_query.prepare("SELECT nummer, vorwahl, daten_id FROM Kontakt WHERE id=:id");
    select_query.prepare("SELECT * FROM Kontakt WHERE daten_id=:daten_id");
}

bool QtKontaktDAO::insert(Kontakt &kontakt)
{
    //bind values (getNummer,...) to values of prepared sql statements (:nummer, ...)
    insert_query.bindValue(":nummer", QString::fromStdString(kontakt.getNummer()));
    insert_query.bindValue(":vorwahl", QString::fromStdString(kontakt.getVorwahl()));
    insert_query.bindValue(":daten_id", kontakt.getDaten()->getId());
    //execute query
    if (!insert_query.exec()) {
        return false;
    }
    //set id of last Inserted ID
    kontakt.setId(insert_query.lastInsertId().toInt());
    return true;
}

bool QtKontaktDAO::update(Kontakt &kontakt)
{
    //bind values (getNummer,...) to values of prepared sql statements (:nummer, ...)
    update_query.bindValue(":nummer", QString::fromStdString(kontakt.getNummer()));
    update_query.bindValue(":vorwahl", QString::fromStdString(kontakt.getVorwahl()));
    update_query.bindValue(":daten_id", kontakt.getDaten()->getId());
    update_query.bindValue(":id", kontakt.getId());
    //execute query
    return update_query.exec();
}

bool QtKontaktDAO::search(Kontakt &kontakt)
{
    //bind value id to ":id" to prepared search query
    search_query.bindValue(":id", kontakt.getId());
    //execute query
    if (!search_query.exec()) {
        return false;
    }
    //execute query
    if (!search_query.next()) {
        return false;
    }
    //setNummer and setVorwahl of konktakt with search query
    kontakt.setNummer(search_query.value(0).toString().toStdString());
    kontakt.setVorwahl(search_query.value(1).toString().toStdString());
    //execute query
    return true;
}

bool QtKontaktDAO::select(Kontakt &kontakt, std::list<Kontakt *> &kontaktList)
{
    //bind value id to ":daten_id" to prepared select query
    select_query.bindValue(":daten_id", kontakt.getDaten()->getId());
    //execute query
    if (!select_query.exec()) {
        return false;
    }

    //while there is a next query
    while (select_query.next()) {
        //create new object k
        Kontakt *k = new Kontakt();
        //set Id, Nummer, Vorwahl to object k
        k->setId(select_query.value(0).toInt());
        k->setNummer(select_query.value(1).toString().toStdString());
        k->setVorwahl(select_query.value(2).toString().toStdString());
        //set daten
        kontaktList.push_back(k);
    }
    return true;
}
