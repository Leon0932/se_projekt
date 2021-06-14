#ifndef SHOWKLASSENLISTEVIEW_H
#define SHOWKLASSENLISTEVIEW_H

#include <QMainWindow>

#include "daten.h"

namespace Ui {
class ShowKlassenlisteView;
}

class ShowKlassenlisteView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowKlassenlisteView(QWidget *parent = nullptr);
    ShowKlassenlisteView(string email);
    ~ShowKlassenlisteView();

public slots:
    void init();
    void onTablerowDoubleClick(int row, int col);
    void onAusloggenBtnClicked();
    void onAddKlassenmitgliedLblClicked();
    void onMeineDatenBtnClick();

private:
    Ui::ShowKlassenlisteView *ui;
    string email;
};

#endif // SHOWKLASSENLISTEVIEW_H
