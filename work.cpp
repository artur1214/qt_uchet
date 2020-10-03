#include "work.h"
#include "ui_work.h"
#include "appsettings.h"
#include "dbmanager.h"
#include "workswidget.h"

Work::Work(QString date, QString desc, QString id, QString user, QWidget *parent) :
QWidget(parent),
ui(new Ui::Work)
{
    this->id = id;
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    if(user == AppSettings::curUser){
        //connect(ui->editBtn, SIGNAL(clicked()), this, SLOT(removeWork()));
    }
    else {
        //ui->editBtn->hide();
        //ui->deleteBtn->hide();
    }
    //this->ui->
    //this->setStyleSheet("QFrame#myWidget {border 1px solid; border-radius: 2px}")");
    //this->setStyleSheet("border: 1px solid red");
    ui->plainTextEdit->setPlainText(date + " | " + desc);

    //if()
}

Work::~Work()
{
    delete ui;
}

void Work::mouseDoubleClickEvent(QMouseEvent *)
{
    if(this->editable){
        //WorksWidget * edit = new WorksWidget(1)
    }
}

void Work::removeWork()
{
    if(DBManager::instance()->removeWork(this->id) == 1){
            emit deleted();
            return;
        }
        else {

        }
}
