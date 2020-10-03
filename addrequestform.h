#ifndef ADDREQUESTFORM_H
#define ADDREQUESTFORM_H

#include "dbmanager.h"

#include <QDialog>

namespace Ui {
class AddRequestForm;
}

class AddRequestForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddRequestForm(QWidget *parent = nullptr);
    ~AddRequestForm();

private slots:
    void onUserChanged(int);
    void onClientChanged(int);
    void onDeviceTypeChanged(int);
    void onDeviceChanged(int);
    void addRequest();

private:
    QList<DBManager::Client> clients;
    QList<DBManager::User> users;
    QList<DBManager::DeviceType> deviceTypes;
    QList<DBManager::Device> devices;
    Ui::AddRequestForm *ui;
    bool showUserAddDialog(QString clientId);
    bool showClientAddDialog();
    void updateClients();
    void updateUsers(QString id = "");
    bool addDeviceType();
    void updateDeviceTypes();
    void updateDevices(QString typeId);
    bool addDevice();
};

#endif // ADDREQUESTFORM_H
