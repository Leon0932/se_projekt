#include <QString>

#include "qtdatendao.h"

#include "klassenmitglied.h"
#include "organisator.h"
#include "organisatordao.h"
#include "qtorganisatordao.h"

QtDatenDAO::QtDatenDAO()
{
    insert_query.prepare("INSERT INTO Daten (name, nachname, geburtsname, email, land, plz, ort, strasse, hausnummer, kommentar, km_id, org_id)"
    "VALUES (:name, :nachname, :geburtsname, :email, :land, :plz, :ort, :strasse, :hausnummer, :kommentar, :km_id, :org_id)");
    search_query.prepare("SELECT * FROM Daten WHERE km_id=:km_id");
    search_email_query.prepare("SELECT * FROM Daten WHERE email=:email");
    select_query.prepare("SELECT * FROM Daten d1 WHERE zeitpunkt = (SELECT max(zeitpunkt) FROM Daten d2 WHERE d1.km_id = d2.km_id);");
    clean_query.prepare("DELETE FROM Daten");
}

bool QtDatenDAO::insert(Daten &daten)
{
    insert_query.bindValue(":name", QString::fromStdString(daten.getName()));
    insert_query.bindValue(":nachname", QString::fromStdString(daten.getNachname()));
    insert_query.bindValue(":geburtsname", QString::fromStdString(daten.getGeburtsname()));
    insert_query.bindValue(":email", QString::fromStdString(daten.getEmail()));
    insert_query.bindValue(":land", QString::fromStdString(daten.getLand()));
    insert_query.bindValue(":plz", daten.getPlz());
    insert_query.bindValue(":ort", QString::fromStdString(daten.getOrt()));
    insert_query.bindValue(":strasse", QString::fromStdString(daten.getStrasse()));
    insert_query.bindValue(":hausnummer", daten.getHausnummer());
    insert_query.bindValue(":kommentar", QString::fromStdString(daten.getKommentar()));
    insert_query.bindValue(":km_id", daten.getKlassenmitglied()->getId());
    insert_query.bindValue(":org_id", daten.getOrganisator()->getId());

    if (!insert_query.exec()) {
        return false;
    }
    daten.setId(insert_query.lastInsertId().toInt());
    return true;
}

bool QtDatenDAO::update(Daten &daten)
{
    return true;
}

bool QtDatenDAO::remove(int id)
{
    return true;
}

bool QtDatenDAO::search(Daten &daten, std::list<Daten *> &datenList)
{
    search_query.bindValue(":km_id", daten.getKlassenmitglied()->getId());
    if (!search_query.exec()) {
        return false;
    }
    while (search_query.next()) {
        Daten* d = new Daten();
        d->setId(search_query.value(0).toInt());
        d->setEmail(search_query.value(1).toString().toStdString());
        d->setName(search_query.value(2).toString().toStdString());
        d->setNachname(search_query.value(3).toString().toStdString());
        d->setGeburtsname(search_query.value(4).toString().toStdString());
        d->setLand(search_query.value(5).toString().toStdString());
        d->setPlz(search_query.value(6).toInt());
        d->setOrt(search_query.value(7).toString().toStdString());
        d->setStrasse(search_query.value(8).toString().toStdString());
        d->setHausnummer(search_query.value(9).toInt());
        d->setKommentar(search_query.value(10).toString().toStdString());

        datenList.push_back(d);
    }
    return true;
}

bool QtDatenDAO::searchEmail(Daten &daten)
{
    search_email_query.bindValue(":email", QString::fromStdString(daten.getEmail()));
    if (!search_email_query.exec()) {
        return false;
    }
    if (!search_email_query.next()) {
        return false;
    }

    Klassenmitglied km = Klassenmitglied();
    km.setId(search_email_query.value(13).toInt());
    Organisator org = Organisator();
    org.setId(km.getId());
    OrganisatorDAO* odao = new QtOrganisatorDAO();
    odao->search(org);

    daten.setId(search_email_query.value(0).toInt());
    daten.setEmail(search_email_query.value(1).toString().toStdString());
    daten.setName(search_email_query.value(2).toString().toStdString());
    daten.setNachname(search_email_query.value(3).toString().toStdString());
    daten.setGeburtsname(search_email_query.value(4).toString().toStdString());
    daten.setLand(search_email_query.value(5).toString().toStdString());
    daten.setPlz(search_email_query.value(6).toInt());
    daten.setOrt(search_email_query.value(7).toString().toStdString());
    daten.setStrasse(search_email_query.value(8).toString().toStdString());
    daten.setHausnummer(search_email_query.value(9).toInt());
    daten.setKommentar(search_email_query.value(10).toString().toStdString());
    daten.setTimestamp(search_email_query.value(11).toString().toStdString());
    daten.setKlassenmitglied(&km);
    daten.setOrganisator(&org);

    return true;
}

bool QtDatenDAO::select(Daten &daten, std::list<Daten *> *datenList)
{
    if (!select_query.exec()) {
        return false;
    }

    while (select_query.next()) {
        Daten* d = new Daten();
        d->setId(select_query.value(0).toInt());
        d->setEmail(select_query.value(1).toString().toStdString());
        d->setName(select_query.value(2).toString().toStdString());
        d->setNachname(select_query.value(3).toString().toStdString());
        d->setGeburtsname(select_query.value(4).toString().toStdString());
        d->setLand(select_query.value(5).toString().toStdString());
        d->setPlz(select_query.value(6).toInt());
        d->setOrt(select_query.value(7).toString().toStdString());
        d->setStrasse(select_query.value(8).toString().toStdString());
        d->setHausnummer(select_query.value(9).toInt());
        d->setKommentar(select_query.value(10).toString().toStdString());

        datenList->push_back(d);
    }
    return true;
}

bool QtDatenDAO::clean()
{
    return clean_query.exec();
}
