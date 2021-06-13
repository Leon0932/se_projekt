#ifndef SHOWKLASSENLISTEVIEW_H
#define SHOWKLASSENLISTEVIEW_H

#include <QMainWindow>

namespace Ui {
class ShowKlassenlisteView;
}

class ShowKlassenlisteView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowKlassenlisteView(QWidget *parent = nullptr);
    ~ShowKlassenlisteView();

public slots:
    void init();
    void onTablerowClicked(int row, int col);
    void onTablerowDoubleClick(int row, int col);
    void onAusloggenBtnClicked();
    void onAddKlassenmitgliedLblClicked();
    void onShowProfileLblClicked();

private:
    Ui::ShowKlassenlisteView *ui;
};

#endif // SHOWKLASSENLISTEVIEW_H
