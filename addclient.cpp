#include "addclient.h"
#include "dbmanager.h"
#include "ui_addclient.h"

void AddClient::addClient()
{
    if(ui->client->text() == ""){
        ui->errorLabel->setText("Введите название клиента");
    }
    else{
        if(DBManager::instance()->addClient(ui->client->text()) == 1){
            accept();
        }
        else{
            ui->errorLabel->setText("Неизвестная ошибка");
        }
    }
    //close();
}

AddClient::AddClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClient)
{
    ui->setupUi(this);
    connect(ui->addBtn, SIGNAL( clicked() ), this, SLOT(addClient()));
    //setAttribute(Qt::WA_DeleteOnClose);
}

AddClient::~AddClient()
{
    //reject();
    delete ui;
}
