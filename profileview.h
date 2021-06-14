#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include <QWidget>

#include <string>
#include "daten.h"
#include <list>

namespace Ui {
class ProfileView;
}

class ProfileView : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileView(QWidget *parent = nullptr);
    ProfileView(std::string email);
    ~ProfileView();

public slots:
    void onOkBtnClick();
    void onuebernehmenBtnClick();
    void abbBtnClick();
    void pwAendernBtnClick();
    void orgRechteBtnClick();
    void kontakteBtnClick();

private:
    Ui::ProfileView *ui;
    std::list<Daten*> datenList;
    void initTbx(int listPos);
};

#endif // PROFILEVIEW_H
