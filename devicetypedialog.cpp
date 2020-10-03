#include "devicetypedialog.h"
#include "ui_devicetypedialog.h"
#include "dbmanager.h"
DeviceTypeDialog::DeviceTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceTypeDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);

    //connect(ui->checkBox, SIGNAL(stateChanged(int)), SLOT(showPass(int)));
    connect(ui->cancelBtn, SIGNAL( clicked() ), SLOT( reject() ) );
    connect(ui->addBtn, SIGNAL( clicked() ), SLOT( addDeviceType() ) );
}

DeviceTypeDialog::~DeviceTypeDialog()
{
    delete ui;
}

void DeviceTypeDialog::addDeviceType()
{
    int addingRes = DBManager::instance()->addDeviceType(ui->nameInp->text());
    if(addingRes == 1){
        accept();
    }
    else if(addingRes == 19){
        ui->errorLabel->setText("Ошибка, данный тип устройства \nуже зарегестрирован в БД");
        //ui->passInp->setText("");
    }
    else{
        qDebug() << "Неизвесная ошибка " << addingRes;
    }
}
