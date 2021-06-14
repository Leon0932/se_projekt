#include <QString>

#include "qtdatendao.h"

#include "klassenmitglied.h"
#include "organisator.h"
#include "organisatordao.h"
#include "qtorganisatordao.h"
#include "qtkontaktdao.h"

QtDatenDAO::QtDatenDAO()
{
    insert_query.prepare("INSERT INTO Daten (name, nachname, geburtsname, email, land, plz, ort, strasse, hausnummer, kommentar, km_id, org_id)"
    "VALUES (:name, :nachname, :geburtsname, :email, :land, :plz, :ort, :strasse, :hausnummer, :kommentar, :km_id, :org_id)");
    updateHK_query.prepare("UPDATE Daten SET hauptkontakt=:hk_id WHERE id=:id;");
    search_query.prepare("SELECT * FROM Daten WHERE km_id=:km_id");
    search_email_query.prepare("SELECT * FROM Daten WHERE email=:email");
    select_newest_query.prepare("SELECT * FROM Daten d1 WHERE km_id=:km_id AND zeitpunkt = (SELECT max(zeitpunkt) FROM Daten d2 WHERE d1.km_id=d2.km_id);");
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

bool QtDatenDAO::updateHauptkontakt(Daten &daten)
{
    //updateHK_query.prepare("UPDATE Daten SET hauptkontakt=:hk_id WHERE id=:id;");
    //UPDATE Daten SET hauptkontakt=11 WHERE id=15
    updateHK_query.bindValue(":hk_id", daten.getHauptkontakt()->getId());
    updateHK_query.bindValue(":id", daten.getId());

    return updateHK_query.exec();
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
        Organisator *org = new Organisator();
        org->setId(search_query.value(14).toInt());
        OrganisatorDAO* odao = new QtOrganisatorDAO();
        odao->search(*org);
        Kontakt *k = new Kontakt();
        k->setId(search_query.value(12).toInt());
        KontaktDAO *kdao = new QtKontaktDAO();
        kdao->search(*k);

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
        d->setOrganisator(org);
        d->setHauptkontakt(k);

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

    Klassenmitglied *km = new Klassenmitglied();
    km->setId(search_email_query.value(13).toInt());
    Organisator *org = new Organisator();
    org->setId(search_email_query.value(14).toInt());
    OrganisatorDAO* odao = new QtOrganisatorDAO();
    odao->search(*org);
    Kontakt *k = new Kontakt();
    k->setId(search_email_query.value(12).toInt());
    KontaktDAO *kdao = new QtKontaktDAO();
    kdao->search(*k);

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
    daten.setKlassenmitglied(km);
    daten.setOrganisator(org);
    daten.setHauptkontakt(k);

    return true;
}

bool QtDatenDAO::select_newest(Daten &daten)
{
    select_newest_query.bindValue(":km_id", daten.getKlassenmitglied()->getId());
    if (!select_newest_query.exec()) {
        return false;
    }
    if (!select_newest_query.next()) {
        return false;
    }
    daten.setId(select_newest_query.value(0).toInt());
    daten.setEmail(select_newest_query.value(1).toString().toStdString());
    daten.setName(select_newest_query.value(2).toString().toStdString());
    daten.setNachname(select_newest_query.value(3).toString().toStdString());

    return true;
}

bool QtDatenDAO::select(Daten &daten, std::list<Daten *> *datenList)
{
    if (!select_query.exec()) {
        return false;
    }

    while (select_query.next()) {

        Organisator *org = new Organisator();
        org->setId(select_query.value(14).toInt());
        OrganisatorDAO* odao = new QtOrganisatorDAO();
        odao->search(*org);

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
        d->setOrganisator(org);

        datenList->push_back(d);
    }
    return true;
}

bool QtDatenDAO::clean()
{
    return clean_query.exec();
}
