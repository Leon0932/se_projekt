#include <QString>

#include "qtkontaktdao.h"
#include "daten.h"

QtKontaktDAO::QtKontaktDAO()
{
    insert_query.prepare("INSERT INTO Kontakt (nummer, vorwahl, daten_id) VALUES (:nummer, :vorwahl, :daten_id)");
    update_query.prepare("UPDATE Kontakt SET nummer=:nummer, vorwahl=:vorwahl, daten_id=:daten_id WHERE id=:id");
    search_query.prepare("SELECT nummer, vorwahl, daten_id FROM Kontakt WHERE id=:id");
    select_query.prepare("SELECT * FROM Kontakt WHERE daten_id=:daten_id");
}

bool QtKontaktDAO::insert(Kontakt &kontakt)
{
    insert_query.bindValue(":nummer", QString::fromStdString(kontakt.getNummer()));
    insert_query.bindValue(":vorwahl", QString::fromStdString(kontakt.getVorwahl()));
    insert_query.bindValue(":daten_id", kontakt.getDaten()->getId());
    if (!insert_query.exec()) {
        return false;
    }
    kontakt.setId(insert_query.lastInsertId().toInt());
    return true;
}

bool QtKontaktDAO::update(Kontakt &kontakt)
{
    update_query.bindValue(":nummer", QString::fromStdString(kontakt.getNummer()));
    update_query.bindValue(":vorwahl", QString::fromStdString(kontakt.getVorwahl()));
    update_query.bindValue(":daten_id", kontakt.getDaten()->getId());
    update_query.bindValue(":id", kontakt.getId());
    return update_query.exec();
}

bool QtKontaktDAO::search(Kontakt &kontakt)
{
    search_query.bindValue(":id", kontakt.getId());
    if (!search_query.exec()) {
        return false;
    }
    if (!search_query.next()) {
        return false;
    }
    kontakt.setNummer(search_query.value(0).toString().toStdString());
    kontakt.setVorwahl(search_query.value(1).toString().toStdString());
    //set daten
    return true;
}

bool QtKontaktDAO::select(Kontakt &kontakt, std::list<Kontakt *> &kontaktList)
{
    select_query.bindValue(":daten_id", kontakt.getDaten()->getId());
    if (!select_query.exec()) {
        return false;
    }

    while (select_query.next()) {
        Kontakt *k = new Kontakt();
        k->setId(select_query.value(0).toInt());
        k->setNummer(select_query.value(1).toString().toStdString());
        k->setVorwahl(select_query.value(2).toString().toStdString());
        //set daten
        kontaktList.push_back(k);
    }
    return true;
}
