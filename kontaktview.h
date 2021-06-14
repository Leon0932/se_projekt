#ifndef KONTAKTVIEW_H
#define KONTAKTVIEW_H

#include <QWidget>
#include <list>

#include "createhauptorganisatorview.h"
#include "kontakt.h"

namespace Ui {
class KontaktView;
}

class KontaktView : public QWidget
{
    Q_OBJECT

public:
    explicit KontaktView(QWidget *parent = nullptr);
    explicit KontaktView(CreateHauptorganisatorView *baseForm, list<Kontakt*> &kList);
    ~KontaktView();

public slots:
    void onAddBtnClick();
    void onRemBtnClick();
    void onOkBtnClick();
    void onAbbBtnClick();

private:
    Ui::KontaktView *ui;
    CreateHauptorganisatorView *baseForm;
    void updateComboBox();
};

#endif // KONTAKTVIEW_H
