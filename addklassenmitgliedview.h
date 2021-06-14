#ifndef ADDKLASSENMITGLIEDVIEW_H
#define ADDKLASSENMITGLIEDVIEW_H

#include <QMainWindow>
#include <string>
#include <list>
#include "qtkontaktdao.h"

using std::string;

namespace Ui {
class AddKlassenmitgliedView;
}

class AddKlassenmitgliedView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddKlassenmitgliedView(QWidget *parent = nullptr);
    AddKlassenmitgliedView(string email);
    ~AddKlassenmitgliedView();

public slots:
    void onKontakteBtnClicked();
    void onKlassenlisteBtnClicked();
    void onMeineDatenBtnClicked();
    void onUebernehmenBtnClicked();
    void onAbbrechenBtnClicked();
    void onAusloggenBtnClicked();

private:
    Ui::AddKlassenmitgliedView *ui;
    string email;
    std::list<Kontakt*> kontaktList;
    int hauptKontaktPos = -1;
};

#endif // ADDKLASSENMITGLIEDVIEW_H
