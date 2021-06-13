#ifndef KONTAKTVIEW_H
#define KONTAKTVIEW_H

#include <QWidget>

namespace Ui {
class KontaktView;
}

class KontaktView : public QWidget
{
    Q_OBJECT

public:
    explicit KontaktView(QWidget *parent = nullptr);
    ~KontaktView();

public slots:
    void onAddBtnClick();
    void onRemBtnClick();
    void onOkBtnClick();
    void onAbbBtnClick();

private:
    Ui::KontaktView *ui;
    void updateComboBox();
};

#endif // KONTAKTVIEW_H
