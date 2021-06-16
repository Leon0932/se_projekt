#ifndef SHOWKLASSENLISTEVIEW_H
#define SHOWKLASSENLISTEVIEW_H

#include <QMainWindow>

#include "daten.h"

namespace Ui {
class ShowKlassenlisteView;
}

// GUI Klasse um die Klassenliste zu zeigen
class ShowKlassenlisteView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowKlassenlisteView(QWidget *parent = nullptr);
    //Konstruktor mit der Email des aktuell angemeldeten Organisators
    ShowKlassenlisteView(string email);
    ~ShowKlassenlisteView();

public slots:
    //setzt die Listview mit den neuesten Daten der Klassenmitglieder
    void init();
    //QT Slots für Btn Events der GUI
    void onTablerowDoubleClick(int row, int col);
    void onAusloggenBtnClicked();
    void onAddKlassenmitgliedLblClicked();
    void onMeineDatenBtnClick();

private:
    Ui::ShowKlassenlisteView *ui;
    //email des aktuell angemeldeten Organisators
    string email;
};

#endif // SHOWKLASSENLISTEVIEW_H
