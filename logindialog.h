#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "dbmanager.h"

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
   // explicit LoginDialog(bool error);
    ~LoginDialog();
    QString getLogin();
    QString getPass();
private slots:
    void showPass(int);
    void tryLogin();

private:
    Ui::LoginDialog *ui;
    //DBManager *db;
};

#endif // LOGINDIALOG_H
