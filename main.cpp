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

// Deletes all data from every table. Doesn't recreate tables and thus indexes are not reset!
void clean() {
    QtKlassenmitgliedDAO kdao = QtKlassenmitgliedDAO();
    QtOrganisatorDAO odao = QtOrganisatorDAO();
    QtHauptorganisatorDAO hdao = QtHauptorganisatorDAO();
    QtDatenDAO ddao = QtDatenDAO();
    QtKontaktDAO kodao = QtKontaktDAO();

    kdao.clean();
    odao.clean();
    hdao.clean();
    ddao.clean();
    kodao.clean();
}

void createTestData() {
    KlassenmitgliedDAO *kdao = new QtKlassenmitgliedDAO();
    OrganisatorDAO *odao = new QtOrganisatorDAO();
    HauptorganisatorDAO *hdao = new QtHauptorganisatorDAO();
    DatenDAO *ddao = new QtDatenDAO();

    Hauptorganisator rd = Hauptorganisator();
    Daten d = Daten("Dietrich", "Roland", "", 0, "", "", 0, "", "roland.dietrich@hs-aalen.de", "");
    d.setKlassenmitglied(&rd);
    d.setOrganisator(&rd);
    kdao->insert(rd);
    odao->insert(rd);
    hdao->insert(rd);
    rd.setPassword("RD");
    odao->update(rd);
    ddao->insert(d);

    sleep_for(seconds(1));
    Organisator mm = Organisator();
    Daten d2 = Daten("Mustermann", "Max", "", 0, "", "", 0, "", "max.mustermann@hs-aalen.de", "");
    d2.setKlassenmitglied(&mm);
    d2.setOrganisator(&rd);
    kdao->insert(mm);
    odao->insert(mm);
    mm.setPassword("MM");
    odao->update(mm);
    ddao->insert(d2);

    sleep_for(seconds(1));
    Organisator km = Organisator();
    Daten d3 = Daten("Musterfrau", "Klara", "", 0, "", "", 0, "", "klara.musterfrau@hs-aalen.de", "");
    d3.setKlassenmitglied(&km);
    d3.setOrganisator(&rd);
    kdao->insert(km);
    odao->insert(km);
    km.setPassword("KM");
    odao->update(km);
    ddao->insert(d3);

    sleep_for(seconds(1));
    Klassenmitglied mp = Klassenmitglied();
    Daten d4 = Daten("Pijarowski", "Matthias", "", 0, "Giengen", "Deutschland", 90537, "Ws", "matthias.pijarowski.hs-aalen.de", "");
    d4.setKlassenmitglied(&mp);
    d4.setOrganisator(&mm);
    kdao->insert(mp);
    ddao->insert(d4);

    sleep_for(seconds(1));
    Daten d5 = Daten("Pijarowski", "Matthias", "", 0, "Giengen", "Deutschland", 90537, "Ws", "matthias.pijarowski@htw-aalen.de", "Die Änderung ist ein Kommentar");
    d5.setKlassenmitglied(&mp);
    d5.setOrganisator(&km);
    ddao->insert(d5);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //check if a param is given and parse it according to specification
    if (argc == 2) {
        string param = argv[1];
        if (param.compare("clean") == 0) {
            cout << "run clean" << endl;
            establishDatabaseConnection();
            clean();
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
