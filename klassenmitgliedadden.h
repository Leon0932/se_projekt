#ifndef KLASSENMITGLIEDADDEN_H
#define KLASSENMITGLIEDADDEN_H

#include <QWidget>

namespace Ui {
class klassenmitgliedAdden;
}

class klassenmitgliedAdden : public QWidget
{
    Q_OBJECT

public:
    explicit klassenmitgliedAdden(QWidget *parent = nullptr);
    ~klassenmitgliedAdden();

private:
    Ui::klassenmitgliedAdden *ui;
};

#endif // KLASSENMITGLIEDADDEN_H
