#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginView; }
QT_END_NAMESPACE

class LoginView : public QWidget
{
    Q_OBJECT

public:
    LoginView(QWidget *parent = nullptr);
    ~LoginView();

public slots:
    void onLoginBtnClicked();
    void onExitBtnClicked();

private:
    Ui::LoginView *ui;
};
#endif // LOGINVIEW_H
