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

private:
    Ui::ShowKlassenlisteView *ui;
};

#endif // SHOWKLASSENLISTEVIEW_H
