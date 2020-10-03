#include "addclient.h"
#include "adduser.h"
#include "dbmanager.h"
#include "ui_adduser.h"
#include <QtDebug>
AddUser::AddUser(QWidget *parent, QString fromRequest) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->addBtn, SIGNAL( clicked() ), SLOT( addUser() ) );
    if(fromRequest!= ""){
        clients = QList<DBManager::Client>();
        clients.append(DBManager::instance()->getClient(fromRequest));
        ui->client->addItem(clients[0].name);
        ui->client->setEnabled(false);
        from = true;
    }
    else {
        ui->client->addItem("Частное обращение");
        ui->client->setEnabled(false);
        //updateClients();
        //clients = QList<DBManager::Client>();
        //clients.append(DBManager::instance()->getClient(fromRequest));
        //connect(ui->client, SIGNAL( activated(int) ), SLOT( onClientChanged(int) ) );
    }
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::addUser()
{
    if(ui->client->currentIndex() == 0){
        if(from){
            DBManager::instance()->addUser(ui->name->text(), clients[0].id, ui->contact->text());
        }
        else {
            DBManager::instance()->addUser(ui->name->text(), "", ui->contact->text());
        }
    }
    else {
        DBManager::instance()->addUser(ui->name->text(), clients[(ui->client->currentIndex())].id, ui->contact->text());
    }
    accept();
}

bool AddUser::showClientAddDialog()
{
    AddClient clientForm(this);
    switch(clientForm.exec()) {
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

void AddUser::onClientChanged(int index)
{
    if(ui->client->count() == (index+1)){
        this->showClientAddDialog();
        //ui->client->setCurrentIndex(index - 1);
    }
}

void AddUser::updateClients()
{
    ui->client->clear();
    clients = DBManager::instance()->getAllClients();
    ui->client->addItem("Частное обращение");
    for(int i = 0; i < clients.length(); i++){
        ui->client->addItem(clients[i].name);
    }
    ui->client->addItem("Добавить");
}
