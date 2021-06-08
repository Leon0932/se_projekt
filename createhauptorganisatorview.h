#ifndef CREATEHAUPTORGANISATORVIEW_H
#define CREATEHAUPTORGANISATORVIEW_H

#include <QWidget>

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
};

#endif // CREATEHAUPTORGANISATORVIEW_H
