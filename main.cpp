#include "loginwindow.h"
#include "createhauptorganisatorview.h"

#include <QApplication>
#include <QtSql>
#include <iostream>
#include <fstream>

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

// Return true if the file db.sqlite exists else return false
bool checkDatabaseExists() {
    if (FILE *file = fopen("./db.sqlite", "r")) {
        fclose(file);
        return true;
    }
    return false;
}

bool establishDatabaseConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./db.sqlite");
    return db.open();
}

bool checkHauptorganistorExists() {
    HauptorganisatorDAO* hdao = new QtHauptorganisatorDAO();
    Hauptorganisator h = Hauptorganisator();
    return hdao->fetch(h);
}

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
        }
    }

    if (!establishDatabaseConnection()) {
        cout << "could not connect to database" << endl;
        return -1;
    }
    if (checkHauptorganistorExists()) {
        LoginWindow w;
        w.show();
        return a.exec();
    }
    else {
        CreateHauptorganisatorView w;
        w.show();
        return a.exec();
    }
}
