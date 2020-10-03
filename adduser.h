#ifndef ADDUSER_H
#define ADDUSER_H

#include "dbmanager.h"

#include <QDialog>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT


public:
    explicit AddUser(QWidget *parent = nullptr, QString fromRequest = "");
    ~AddUser();

signals:
    void clientsUpdated();

private slots:
    void addUser();
    bool showClientAddDialog();
    void onClientChanged(int);
    void updateClients();
private:
    bool from = false;
    Ui::AddUser *ui;
    QList<DBManager::Client> clients;
};

#endif // ADDUSER_H
