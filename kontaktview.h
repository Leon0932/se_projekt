#ifndef KONTAKTVIEW_H
#define KONTAKTVIEW_H

#include <QWidget>
#include <list>

#include "createhauptorganisatorview.h"
#include "addklassenmitgliedview.h"
#include "profileview.h"
#include "kontakt.h"

namespace Ui {
class KontaktView;
}

class KontaktView : public QWidget
{
    Q_OBJECT

public:
    explicit KontaktView(QWidget *parent = nullptr);
    explicit KontaktView(list<Kontakt*> &kList);
    explicit KontaktView(list<Kontakt*> &kList, int &hkPos);
    ~KontaktView();

public slots:
    void onAddBtnClick();
    void onRemBtnClick();
    void onOkBtnClick();
    void onAbbBtnClick();

private:
    Ui::KontaktView *ui;
    int *hauptkontaktPos;
    list<Kontakt*> *kList;
    void updateComboBox();
};

#endif // KONTAKTVIEW_H
