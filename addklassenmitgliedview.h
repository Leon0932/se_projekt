#ifndef ADDKLASSENMITGLIEDVIEW_H
#define ADDKLASSENMITGLIEDVIEW_H

#include <QMainWindow>

namespace Ui {
class AddKlassenmitgliedView;
}

class AddKlassenmitgliedView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddKlassenmitgliedView(QWidget *parent = nullptr);
    ~AddKlassenmitgliedView();

private:
    Ui::AddKlassenmitgliedView *ui;
};

#endif // ADDKLASSENMITGLIEDVIEW_H
