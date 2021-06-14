#ifndef CHANGEPASSWORTVIEW_H
#define CHANGEPASSWORTVIEW_H

#include <QWidget>
#include "qtorganisatordao.h"

namespace Ui {
class ChangePasswortView;
}

class ChangePasswortView : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswortView(QWidget *parent = nullptr);
    ChangePasswortView(Organisator &org, bool openKlassenView);
    ~ChangePasswortView();

public slots:
    void onOkBtnClick();
    void onAbbBtnClick();

private:
    Ui::ChangePasswortView *ui;
    Organisator *org;
    bool openKlassenView = false;
};

#endif // CHANGEPASSWORTVIEW_H
