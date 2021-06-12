#ifndef CHANGEPASSWORTVIEW_H
#define CHANGEPASSWORTVIEW_H

#include <QWidget>

namespace Ui {
class ChangePasswortView;
}

class ChangePasswortView : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswortView(QWidget *parent = nullptr);
    ~ChangePasswortView();

private:
    Ui::ChangePasswortView *ui;
};

#endif // CHANGEPASSWORTVIEW_H
