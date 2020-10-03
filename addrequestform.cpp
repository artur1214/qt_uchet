#include "addclient.h"
#include "adddevice.h"
#include "addrequestform.h"
#include "adduser.h"
#include "dbmanager.h"
#include "devicetypedialog.h"
#include "ui_addrequestform.h"
#include <QtDebug>
#include <QAction>

AddRequestForm::AddRequestForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRequestForm)
{
    //setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    updateClients();
    //ui->client->setI
    updateUsers("");
    updateDeviceTypes();
    connect(ui->client, SIGNAL(activated(int )), this, SLOT(onClientChanged(int)));
    connect(ui->user, SIGNAL(activated(int )), this, SLOT(onUserChanged(int)));
    connect(ui->deviceType, SIGNAL(activated(int )), this, SLOT(onDeviceTypeChanged(int)));
    connect(ui->device, SIGNAL(activated(int )), this, SLOT(onDeviceChanged(int)));
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(addRequest()));
    //qDebug() << ui->problem->placeholderText();
}

AddRequestForm::~AddRequestForm()
{
    delete ui;
}


bool AddRequestForm::showClientAddDialog()
{
    AddClient clientAddForm(this);
    switch(clientAddForm.exec()) {
    case QDialog::Accepted:
        updateClients();
        return true;
    case QDialog::Rejected:
        return false;
    default:
        qDebug() << "Unexpected";
        return false;
    }
}

void AddRequestForm::updateClients()
{
    ui->client->clear();
    clients = DBManager::instance()->getAllClients();
    ui->client->addItem("Частное обращение");
    for(int i = 0; i < clients.length(); i++){
        ui->client->addItem(clients[i].name);
    }
    ui->client->addItem("Добавить");
}

void AddRequestForm::updateUsers(QString id)
{
    ui->user->clear();

    if(id != "")
        users = DBManager::instance()->getAllUsers(id);
    else{
        users = DBManager::instance()->getAllUsers("");
        //qDebug() << "РРР";
    }
    for(int i = 0; i < users.length(); i++){
        ui->user->addItem(users[i].name);
    }
    ui->user->addItem("Добавить...");
}

void AddRequestForm::onUserChanged(int index)
{
    qDebug() << index;
    if(ui->user->count() == (index+1)){
        if(ui->client->currentIndex()!= ui->client->count()-1){
            if(ui->client->currentIndex()== 0){
                showUserAddDialog("");
            }
            else {
                showUserAddDialog(clients[ui->client->currentIndex()-1].id);
            }
        }

    }

}

void AddRequestForm::onClientChanged(int index)
{
    if(ui->client->count() == (index+1)){
        if(showClientAddDialog()){
            updateClients();
            ui->client->setCurrentIndex(clients.length());
            updateUsers(clients[ui->client->currentIndex()+1].id);
        }
    }
    else{
        if(index != 0){
            updateUsers(clients[index-1].id);
        }
        else{
            updateUsers("");
        }
    }

}

void AddRequestForm::onDeviceTypeChanged(int index)
{
    if(index == ui->deviceType->count()-1){
        addDeviceType();
    }
    else {
        updateDevices(deviceTypes[ui->deviceType->currentIndex()].id);
    }
}

void AddRequestForm::onDeviceChanged(int index)
{
    if(index == ui->device->count()-1){
        addDevice();
    }
}

void AddRequestForm::addRequest()
{
    if(DBManager::instance()->addRequest(users[ui->user->currentIndex()].id,
                                         devices[ui->device->currentIndex()].id,
                                         ui->problem->toPlainText(),
    ui->date->date().toString("dd-MM-yyyy"))==1){
        accept();
    }
    else {
        ui->errorLabel->setText("Неизвестная ошибка");
    }

}

bool AddRequestForm::showUserAddDialog(QString clientId)
{
    AddUser userAddForm(this, clientId);
    switch(userAddForm.exec()) {
    case QDialog::Accepted:
        updateUsers();
        return true;
    case QDialog::Rejected:
        return false;
    default:
        qDebug() << "Unexpected";
        return false;
    }
}

void AddRequestForm::updateDeviceTypes(){
    deviceTypes = DBManager::instance()->getDeviceTypes();
    ui->deviceType->clear();
    for(int i = 0; i < deviceTypes.length(); i++){
        ui->deviceType->addItem(deviceTypes[i].name);
    }
    ui->deviceType->addItem("Добавить...");
    if(deviceTypes.length() != 0){
        ui->deviceType->setCurrentIndex(ui->deviceType->count()-2);
        updateDevices(deviceTypes[ui->deviceType->currentIndex()].id);
    }
    else{
        ui->device->setEnabled(false);
    }
    //updateDevices();

}

void AddRequestForm::updateDevices(QString typeId)
{
    ui->device->setEnabled(true);
    ui->device->clear();
    devices = DBManager::instance()->getDevices(typeId);
    for(int i = 0; i < devices.length(); i++){
        ui->device->addItem(devices[i].name);
    }
    ui->device->addItem("Добавить...");
}

bool AddRequestForm::addDevice()
{
    AddDevice deviceAddForm(deviceTypes[ui->deviceType->currentIndex()], this);
    switch(deviceAddForm.exec()) {
    case QDialog::Accepted:
        updateDevices(deviceTypes[ui->deviceType->currentIndex()].id);
        return true;
    case QDialog::Rejected:
        return false;
    default:
        qDebug() << "Unexpected";
        return false;
    }
    //DBManager::instance()->addDevice();
};


bool AddRequestForm::addDeviceType()
{
    DeviceTypeDialog deviceAddForm(this);
    switch(deviceAddForm.exec()) {
    case QDialog::Accepted:
        updateDeviceTypes();
        return true;
    case QDialog::Rejected:
        return false;
    default:
        qDebug() << "Unexpected";
        return false;
    }
}
