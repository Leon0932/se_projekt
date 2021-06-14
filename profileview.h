#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include <QWidget>

#include <string>
#include "daten.h"
#include <list>
#include "qtorganisatordao.h"
#include "qtklassenmitglieddao.h"
#include "showklassenlisteview.h"

namespace Ui {
class ProfileView;
}

class ProfileView : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileView(QWidget *parent = nullptr);
    ProfileView(std::string kmEmail, std::string orgEmail);
    ~ProfileView();
    void addKlassenlistView(ShowKlassenlisteView *kv);
    void loadData();

public slots:
    void onOkBtnClick();
    void onuebernehmenBtnClick();
    void abbBtnClick();
    void pwAendernBtnClick();
    void orgRechteBtnClick();
    void kontakteBtnClick();
    void onPrevBtnClick();
    void onNextBtnClick();

private:
    Ui::ProfileView *ui;
    std::list<Daten*> datenList;
    std::list<Kontakt*> kontaktList;
    std::string kmEmail;
    std::string orgEmail;
    Organisator org;
    Klassenmitglied km;
    ShowKlassenlisteView *kv;
    int listPos;
    void initTbx(int listPos);
};

#endif // PROFILEVIEW_H
