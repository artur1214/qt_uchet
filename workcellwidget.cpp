#include "workcellwidget.h"
#include "ui_workcellwidget.h"
#include "workswidget.h"
#include "dbmanager.h"
#include "mainwindow.h"
#include "work.h"
#include <QResizeEvent>
#include <QtDebug>
#include <QtMath>
WorkCellWidget::WorkCellWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkCellWidget)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

}

WorkCellWidget::WorkCellWidget(QWidget *parent, QList<DBManager::Work> works, QString requestId, int displayType, QString status) :
    QWidget(parent),
    ui(new Ui::WorkCellWidget)
{
    setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);

    //qDebug() << this->styleSheet();
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(addWork()));
    //connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(removeRequest()));
    this->displayType = displayType;
    this->requestId = requestId;
    //this->setStyleSheet("*{background-color: #ABA4C2; border: 1px, solid black; }");
    if(works.length()>0){
        for (int i = 0; i < works.length(); i++) {
            if(displayType == AppSettings::DisplayWorksTypes::Block){
                this->works.append(new WorksWidget(works[i].date, works[i].desc, works[i].id, works[i].user));
                connect(this->works.last(), SIGNAL(deleted()), this, SLOT(onDelete()));
            }
            else if(displayType == AppSettings::DisplayWorksTypes::String){
                this->works.append(new Work(works[i].date, works[i].desc,works[i].id, works[i].user));
            }
        }
        for(int i = 0; i< this->works.length(); i++){
            ui->worksLayout->addWidget(this->works[i], i, 0);

        }
        curColCount = 1;
        if(displayType == AppSettings::DisplayWorksTypes::Block){
            this->setMinimumHeight(qCeil(works.length()/(double)curColCount)*200+28+11+11+7);
            ui->worksLayout->setRowMinimumHeight(0, this->works[0]->minimumHeight());
        }
        else if (displayType == AppSettings::DisplayWorksTypes::String) {
            if(works.length() >0)
                this->setMinimumHeight(qCeil(works.length()/(double)curColCount)*this->works[0]->minimumHeight());
            else {
                this->setMinimumHeight(qCeil(works.length()/(double)curColCount)*60);
            }
        }

    }
}

WorkCellWidget::~WorkCellWidget()
{
    delete ui;
}

void WorkCellWidget::resizeEvent(QResizeEvent *e){
    int colCount;
    if(works.length()>0){
         colCount = e->size().width()/works[0]->maximumWidth();
    }
    else {
         colCount =1;
    }
    if(colCount > this->works.length()){
        colCount = this->works.length();
    }
    QLayoutItem *ch;
    if (colCount != curColCount){
        while ((ch = ui->worksLayout->takeAt(0))!= 0) {
            ui->worksLayout->removeItem(ch);
            //ch->widget()->deleteLater();
            delete ch;
        }
        for(int i = 0; i< this->works.length(); i++){
            ui->worksLayout->addWidget(this->works[i], i/colCount, i%colCount);
            //qDebug() << ui->addBtn->height();
            //ui->worksLayout->setRowMinimumHeight(i/colCount, this->works[0]->minimumHeight());
        }
    }
    //this->setBackgroundRole(QPalette::Dark);
    curColCount = colCount;
    //e->accept();
    //this->setMinimumHeight(qCeil(works.length()/(double)curColCount)*200+28+11+11+7);
    if(displayType == AppSettings::DisplayWorksTypes::Block){
        this->setMinimumHeight(qCeil(works.length()/(double)curColCount)*200+28+11+11+7);
        //ui->worksLayout->setRowMinimumHeight(0, this->works[0]->minimumHeight());
    }
    else if (displayType == AppSettings::DisplayWorksTypes::String) {
        this->setMinimumHeight(qCeil(works.length()/(double)curColCount)*60);
    }
}

void WorkCellWidget::removeRequest()
{
    if(DBManager::instance()->removeRequest(requestId) == 1)
        emit deleted();

}

void WorkCellWidget::addWork()
{
    WorksWidget *dialog = new WorksWidget(this->requestId);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowModality(Qt::WindowModal);
    dialog->show();
    connect(dialog, SIGNAL(deleted()), this, SLOT(onDelete()));
    //WorksWidget *addingWidget = new WorksWidget(this);
    //addingWidget->exec();
    //addingWidget->deleteLater();
}

void WorkCellWidget::onDelete()
{
    emit deleted();
}
