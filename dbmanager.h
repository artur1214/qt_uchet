#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>
#include <QString>
#include <QWidget>
#include <qtablewidget.h>
#include "appsettings.h"

class DBManager
{
public:
    short addWork(QString date, QString desc, QString requestId);
    ~DBManager();
    bool login(QString login, QString password);
    int addDeviceType(QString name);
    short addStatus(QString desc, QString hex);
    AppSettings::RequestStatus getStatus(QString id);
    int user = 0;
    static DBManager* instance(QString name = nullptr);
    short removeWork(QString id);
    short removeRequest(QString id);
    short addRequest(QString userId, QString modelId, QString problem, QString date);
    QList<AppSettings::RequestStatus> getAllRequestStatuses();

private:
    static DBManager* p_instance;
    DBManager(QString dbName);
    DBManager();
    QSqlDatabase sdb;
    QSqlQuery q = QSqlQuery(sdb);


public:
    struct Work{
        QString id;
        QString date;
        QString desc;
        QString request_id;
        QString user;
        Work(QString id, QString date, QString desc, QString request, QString user);
    };
    struct RequestsQuerryRes
    {
        QTableWidgetItem *id;
        QTableWidgetItem *user;
        QTableWidgetItem *model;
        QTableWidgetItem *problem;
        QTableWidgetItem *date;
        QList<Work> works;
        AppSettings::RequestStatus status = AppSettings::RequestStatus("", "", "");
        void createStatus();
        RequestsQuerryRes(QString id, QString user, QString userPhone, QString model, QString problem, QString date, QString status_id);
    };
    struct User{
        QString id;
        QString name;
        QString clientId;
        User(QString id, QString name, QString clientId);
    };

    struct Model{
        QString id;
        QString name;
        QString vendorId;
    };
    struct Client{
        QString id;
        QString name;

        Client(QString id, QString name);
    };
    struct Device{
        QString id;
        QString name;
        QString type;
        Device(QString id, QString name, QString type);
    };
    struct DeviceType{
        QString id;
        QString name;
        DeviceType(QString id, QString name);
    };


    QList<User> getAllUsers();
    QList<User> getAllUsers(QString clientId);
    QList<RequestsQuerryRes> getAllRequests();
    QList<Client> getAllClients();
    Client getClient(QString id);
    short addClient(QString name);
    short addUser(QString name, QString clientId = "", QString contact = "");
    short addDevice(QString name, QString typeId);
    QList<DeviceType> getDeviceTypes();
    QList<Device> getDevices(QString typeId);
    short changeWork(QString id, QString newDate, QString newDesc);
    Work getWork(QString id);
};


#endif // DBMANAGER_H
