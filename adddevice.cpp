#include "adddevice.h"
#include "dbmanager.h"
#include "ui_adddevice.h"

AddDevice::AddDevice(DBManager::DeviceType type, QWidget *parent) :
    QDialog(parent),
    deviceType(type),
    ui(new Ui::AddDevice)
    //deviceType = DBManager
{
    ui->setupUi(this);
    deviceType = type;
    ui->type->addItem(deviceType.name);
    ui->type->setEnabled(false);
    connect(ui->addBtn, SIGNAL( clicked() ), SLOT( addDevice() ) );
}

AddDevice::~AddDevice()
{
    delete ui;
}

void AddDevice::addDevice()
{
    if(ui->name->text().split(" ", QString::SkipEmptyParts).length() == 0){
        ui->errorLabel->setText("Введите название нового устройства");
    }
    else {
        if(DBManager::instance()->addDevice(ui->name->text(), deviceType.id) == 1){
            accept();
        }
        else{
            ui->errorLabel->setText("Неизвестная ошибка.");
        }
    }
    //DBManager::instance()->addDevice(ui->)
}
