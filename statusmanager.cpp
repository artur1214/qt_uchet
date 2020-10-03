#include "colorviewwidget.h"
#include "dbmanager.h"
#include "newstatusform.h"
#include "statusmanager.h"
#include "statussubview.h"
#include "ui_statusmanager.h"

#include <qpushbutton.h>
#include <qsizepolicy.h>

StatusManager::StatusManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusManager)
{
    ui->setupUi(this);
    qDebug() << "запустился конструктор";
    this->statuses = DBManager::instance()->getAllRequestStatuses();
    //ColorViewWidget *colorWidget;
    StatusSubView *status;
    for(int i = 0; i < statuses.length(); i++){
        //ui->gridLayout->addWidget(new QLabel(statuses[i].desc),i+1, 0);
        status = new StatusSubView(statuses[i].id, statuses[i].desc, statuses[i].color);
        //colorWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        //colorWidget->setStyleSheet("QWidget { background-color: " + statuses[i].color + ";}");
        //colorWidget->setBackgroundRole(QPalette())
        ui->gridLayout->addWidget(status, i+1, 0);
    }
    QPushButton * addBtn = new QPushButton("Добавить", this);
    ui->gridLayout->addWidget(addBtn);
    connect(addBtn, SIGNAL(clicked()), this, SLOT(addStatus()));
}

StatusManager::~StatusManager()
{
    delete ui;
}

bool StatusManager::addStatus()
{
    NewStatusForm newStatusForm(this);
    switch(newStatusForm.exec()) {
    case QDialog::Accepted:
        updateStatuses();
        return true;
    case QDialog::Rejected:
        return false;
    default:
        qDebug() << "Unexpected";
        return false;
    }
}

void StatusManager::updateStatuses()
{

}
