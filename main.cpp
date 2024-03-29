#include "loginview.h"
#include "createhauptorganisatorview.h"

#include <QApplication>
#include <QtSql>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "klassenmitglied.h"

#include "hauptorganisator.h"
#include "hauptorganisatordao.h"

#include "qthauptorganisatordao.h"
#include "qtklassenmitglieddao.h"
#include "qtorganisatordao.h"
#include "qtdatendao.h"
#include "qtkontaktdao.h"

using std::cout;
using std::endl;
using std::string;
using namespace std::this_thread;
using namespace std::chrono;

// Return true if the file db.sqlite exists else return false
bool checkDatabaseExists() {
    if (FILE *file = fopen("./db.sqlite", "r")) {
        fclose(file);
        return true;
    }
    return false;
}

// Return true when database connection is open else return false
bool establishDatabaseConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./db.sqlite");
    return db.open();
}

// Creates the database tables
void createDatabaseTables() {
    QSqlQuery create_query;
    create_query.prepare("CREATE TABLE \"Klassenmitglied\" ("
                            "\"id\" INTEGER NOT NULL UNIQUE, "
                            "PRIMARY KEY(\"id\" AUTOINCREMENT)"
                        ");");
    create_query.exec();
    create_query.prepare("CREATE TABLE \"Organisator\" ("
                            "\"km_id\" INTEGER,"
                            "\"passwort\" TEXT DEFAULT 'password',"
                            "PRIMARY KEY(\"km_id\"),"
                            "FOREIGN KEY(\"km_id\") REFERENCES \"Klassenmitglied\"(\"id\") on delete cascade"
                        ");");
    create_query.exec();
    create_query.prepare("CREATE TABLE \"Hauptorganisator\" ("
                            "\"org_id\"	INTEGER NOT NULL,"
                            "PRIMARY KEY(\"org_id\"),"
                            "FOREIGN KEY(\"org_id\") REFERENCES \"Organisator\"(\"km_id\") on delete cascade"
                        ");");
    create_query.exec();
    create_query.prepare("CREATE TABLE \"Daten\" ("
                            "\"id\"	INTEGER NOT NULL UNIQUE,"
                            "\"email\"	TEXT,"
                            "\"name\"	TEXT NOT NULL,"
                            "\"nachname\"	TEXT NOT NULL,"
                            "\"geburtsname\"	TEXT,"
                            "\"land\"	TEXT,"
                            "\"plz\"	INTEGER,"
                            "\"ort\"	TEXT,"
                            "\"strasse\"	TEXT,"
                            "\"hausnummer\"	INTEGER,"
                            "\"kommentar\"	TEXT,"
                            "\"zeitpunkt\"	TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                            "\"hauptkontakt\"	INTEGER DEFAULT NULL,"
                            "\"km_id\"	INTEGER NOT NULL,"
                            "\"org_id\"	INTEGER NOT NULL,"
                            "PRIMARY KEY(\"id\" AUTOINCREMENT),"
                            "FOREIGN KEY(\"org_id\") REFERENCES \"Organisator\"(\"km_id\"),"
                            "FOREIGN KEY(\"hauptkontakt\") REFERENCES \"Kontakt\"(\"id\") on delete set default,"
                            "FOREIGN KEY(\"km_id\") REFERENCES \"Klassenmitglied\"(\"id\") on delete cascade"
                        ");");
    create_query.exec();
    create_query.prepare("CREATE TABLE \"Kontakt\" ("
                            "\"id\"	INTEGER NOT NULL UNIQUE,"
                            "\"nummer\"	TEXT,"
                            "\"vorwahl\"	TEXT,"
                            "\"daten_id\"	INTEGER NOT NULL,"
                            "FOREIGN KEY(\"daten_id\") REFERENCES \"Daten\"(\"id\"),"
                            "PRIMARY KEY(\"id\" AUTOINCREMENT)"
                        ");");
    create_query.exec();
}

// Return true if a hauptorganisator exists else Return false
// Useful to determine whether the login or createHauptorganisator window should be shown on program start
bool checkHauptorganistorExists() {
    HauptorganisatorDAO* hdao = new QtHauptorganisatorDAO();
    Hauptorganisator h = Hauptorganisator();
    return hdao->fetch(h);
}

void createTestData() {
    KlassenmitgliedDAO *kdao = new QtKlassenmitgliedDAO();
    OrganisatorDAO *odao = new QtOrganisatorDAO();
    HauptorganisatorDAO *hdao = new QtHauptorganisatorDAO();
    DatenDAO *ddao = new QtDatenDAO();

    Hauptorganisator rd = Hauptorganisator();
    Daten d = Daten("Dietrich", "Roland", "", 1, "", "", 11111, "", "roland.dietrich@hs-aalen.de", "");
    d.setKlassenmitglied(&rd);
    d.setOrganisator(&rd);
    kdao->insert(rd);
    odao->insert(rd);
    hdao->insert(rd);
    rd.setPassword("RD");
    odao->update(rd);
    ddao->insert(d);

    Organisator mm = Organisator();
    Daten d2 = Daten("Mustermann", "Max", "", 2, "", "", 22222, "", "max.mustermann@hs-aalen.de", "");
    d2.setKlassenmitglied(&mm);
    d2.setOrganisator(&rd);
    kdao->insert(mm);
    odao->insert(mm);
    mm.setPassword("MM");
    odao->update(mm);
    ddao->insert(d2);

    Organisator km = Organisator();
    Daten d3 = Daten("Musterfrau", "Klara", "", 3, "", "", 33333, "", "klara.musterfrau@hs-aalen.de", "");
    d3.setKlassenmitglied(&km);
    d3.setOrganisator(&rd);
    kdao->insert(km);
    odao->insert(km);
    km.setPassword("KM");
    odao->update(km);
    ddao->insert(d3);

    Klassenmitglied mp = Klassenmitglied();
    Daten d4 = Daten("Pijarowski", "Matthias", "", 5, "Giengen", "Deutschland", 90537, "Wildermuthstraße", "matthias.pijarowski.hs-aalen.de", "");
    d4.setKlassenmitglied(&mp);
    d4.setOrganisator(&mm);
    kdao->insert(mp);
    ddao->insert(d4);

    Klassenmitglied sm = Klassenmitglied();
    Daten d6 = Daten("Mayer", "Sven", "Müller", 2, "Aalen", "Deutschland", 54312, "aalstraße", "sven.mayer@htw-aalen.de", "Kommt mit Freundin.");
    d6.setKlassenmitglied(&sm);
    d6.setOrganisator(&km);
    kdao->insert(sm);
    ddao->insert(d6);

    Klassenmitglied nb = Klassenmitglied();
    Daten d7 = Daten("Banea", "Nikolas", "", 14, "Schwäbisch Gmünd", "Deutschland", 71325, "Schwabenstraße", "nikolas.banea@htw-aalen.de", "Kommt erst um 22:30 Uhr");
    d7.setKlassenmitglied(&nb);
    d7.setOrganisator(&mm);
    kdao->insert(nb);
    ddao->insert(d7);

    Klassenmitglied jb = Klassenmitglied();
    Daten d8 = Daten("Bäuml", "Julian", "", 22, "Stuttgart", "Deutschland", 84612, "Stuttgarterstraße", "julian.baeuml@htw-aalen.de", "Bringt Essen mit.");
    d8.setKlassenmitglied(&jb);
    d8.setOrganisator(&km);
    kdao->insert(jb);
    ddao->insert(d8);

    Klassenmitglied ev = Klassenmitglied();
    Daten d9 = Daten("Vogt", "Erwin", "", 42, "Mannheim", "Deutschland", 89123, "Mannstraße", "erwin_09@gmx.de", "");
    d9.setKlassenmitglied(&ev);
    d9.setOrganisator(&km);
    kdao->insert(ev);
    ddao->insert(d9);

    Klassenmitglied mh = Klassenmitglied();
    Daten d10 = Daten("Höfer", "Michelle", "", 1, "Freiburg", "Deutschland", 71234, "Freistraße", "michelle-hoefer@gmx.de", "Kommt mit Mann und Kind");
    d10.setKlassenmitglied(&mh);
    d10.setOrganisator(&mm);
    kdao->insert(mh);
    ddao->insert(d10);

    Klassenmitglied ay = Klassenmitglied();
    Daten d11 = Daten("Yildiz", "Abdullah", "", 5, "Westhausen", "Deutschland", 81345, "Weststraße", "abdullah.yildiz@htw-aalen.de", "Bringt Trinken mit.");
    d11.setKlassenmitglied(&ay);
    d11.setOrganisator(&mm);
    kdao->insert(ay);
    ddao->insert(d11);

    Klassenmitglied sh = Klassenmitglied();
    Daten d12 = Daten("Schneider", "Hanna", "", 42, "Waiblingen", "Deutschland", 71332, "Stauferstraße", "hannah.schneider@gmx.de", "");
    d12.setKlassenmitglied(&sh);
    d12.setOrganisator(&km);
    kdao->insert(sh);
    ddao->insert(d12);

    Klassenmitglied sm2 = Klassenmitglied();
    Daten d13 = Daten("Schmidt", "Mia", "", 1, "Stuttgart", "Deutschland", 70173, "Mittlerer Schloßgarten", "mia_schmidt@gmail.com", "Kommt mit verspätung.");
    d13.setKlassenmitglied(&sm2);
    d13.setOrganisator(&km);
    kdao->insert(sm2);
    ddao->insert(d13);

    Klassenmitglied wa = Klassenmitglied();
    Daten d14 = Daten("Wagner", "Albert", "", 5, "Berlin", "Deutschland", 10115, "Torstraße", "albert.wagner@htw-aalen.de", "Bringt Essen mit.");
    d14.setKlassenmitglied(&wa);
    d14.setOrganisator(&km);
    kdao->insert(wa);
    ddao->insert(d14);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //check if a param is given and parse it according to specification
    if (argc == 2) {
        string param = argv[1];
        if (param.compare("clean") == 0) {
            cout << "run clean" << endl;
            if (checkDatabaseExists()) {
                std::remove("db.sqlite");
                sleep_for(seconds(3)); //sleep so the db file get deleted
            }
            establishDatabaseConnection();
            createDatabaseTables();
            return 0;
        } else if (param.compare("test") == 0) {
            cout << "run test" << endl;
            if (checkDatabaseExists()) {
                std::remove("db.sqlite");
                sleep_for(seconds(3)); //sleep so the db file get deleted
            }
            cout << "create new Database..." << endl;
            establishDatabaseConnection();
            createDatabaseTables();
            cout << "create test Data..." << endl;
            createTestData();
            return 0;
        }
    }

    if (!checkDatabaseExists()) {
        //if db doesnt exist create new db.sqlite file and run create Statements
        establishDatabaseConnection();
        createDatabaseTables();
    } else if (!establishDatabaseConnection()) {
        cout << "could not connect to database" << endl;
        return -1;
    }

    // if hauptorganisator exists show the login window else create a new hauptorganisator
    if (checkHauptorganistorExists()) {
        LoginView w;
        w.show();
        return a.exec();
    }
    else {
        CreateHauptorganisatorView w;
        w.show();
        return a.exec();
    }
}
