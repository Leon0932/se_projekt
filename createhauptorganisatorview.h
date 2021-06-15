#ifndef CREATEHAUPTORGANISATORVIEW_H
#define CREATEHAUPTORGANISATORVIEW_H

#include <QWidget>
#include <list>
using std::list;

#include "kontakt.h"

namespace Ui {
class CreateHauptorganisatorView;
}

class CreateHauptorganisatorView : public QWidget
{
    Q_OBJECT

public:
    explicit CreateHauptorganisatorView(QWidget *parent = nullptr);
    ~CreateHauptorganisatorView();

public slots:
    void onKontakteBtnClicked();
    void onSaveBtnClicked();
    void onExitBtnClicked();

private:
    Ui::CreateHauptorganisatorView *ui;
    list<Kontakt*> kontaktList;
    int hauptKontaktPos = -1;
};

#endif // CREATEHAUPTORGANISATORVIEW_H
