#include "workswidget.h"
#include "ui_workswidget.h"
#include "dbmanager.h"
#include "appsettings.h"
#include <QCalendarWidget>

void WorksWidget::showCalendar()
{
    this->settings->show();
}

void WorksWidget::saveWork()
{
    QString date = this->settings->date.toString("yyyy-MM-dd");
    if(DBManager::instance()->addWork(date, ui->desc->toPlainText(), this->requestId) == 1){
        emit deleted();
        this->close();
    }
    else {
        return;
    }

}

void WorksWidget::showDate()
{
    ui->date->setText(this->settings->date.toString("yyyy-MM-dd"));

}

void WorksWidget::cancel()
{
    this->close();
}

void WorksWidget::removeWork()
{
    if(DBManager::instance()->removeWork(this->id) == 1){
        emit deleted();
        return;
    }
    else {

    }
}

void WorksWidget::editWork()
{
    if(DBManager::instance()->changeWork(this->id, ui->date->text(), ui->desc->toPlainText())){
        emit deleted();
        this->close();
    }
}

void WorksWidget::updateWork()
{
    DBManager::Work w = DBManager::instance()->getWork(this->id);
    ui->date->setText(w.date);
    ui->desc->setText(w.desc);
    this->requestId = w.request_id;
}

void WorksWidget::showEditDialog()
{
    WorksWidget *dialog = new WorksWidget(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowModality(Qt::WindowModal);
    dialog->show();
    connect(dialog, SIGNAL(deleted()), this, SLOT(updateWork()));
}

WorksWidget::WorksWidget(QString RequestId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorksWidget)
{
    ui->setupUi(this);
    this->requestId = RequestId;
    this->settings = new WorkSettings();
    connect(ui->dateBtn, SIGNAL(clicked()), this, SLOT(showCalendar()));
    connect(this->settings, SIGNAL(WidgetClosed()), this, SLOT(showDate()));
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(saveWork()));
    this->setMaximumSize(QSize(640, 480));
    ui->desc->setMaximumHeight(600);
    ui->date->setEnabled(false);
    ui->deleteBtn->setText("Отмена");
    connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(cancel()));
    //this-
}

WorksWidget::WorksWidget(WorksWidget *parent) :
    //QWidget(parent),
    ui(new Ui::WorksWidget)
{
    ui->setupUi(this);
    this->from = parent;
    this->id = parent->id;
    qDebug() << "рАБОТАЕТ";
    ui->date->setText(parent->curDate);
    ui->desc->setPlainText(parent->curDesc);
    qDebug() << "Работает123!!!!!";
    ui->addBtn->setText("Сохранить");
    ui->deleteBtn->setText("Отмена");
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(editWork()));
    connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(close()));
    this->settings = new WorkSettings();
    connect(ui->dateBtn, SIGNAL(clicked()), this, SLOT(showCalendar()));
    connect(this->settings, SIGNAL(WidgetClosed()), this, SLOT(showDate()));
}

WorksWidget::WorksWidget(QString date, QString desc, QString id, QString user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorksWidget)
{
    //DBManager::
    this->id = id;
    ui->setupUi(this);
    ui->dateBtn->hide();
    this->curDesc = desc;
    this->curDate = date;
    this->settings = new WorkSettings();
    //connect(ui->dateBtn, SIGNAL(clicked()), this, SLOT(showCalendar()));
    if(user == AppSettings::curUser){
        //ui->addBtn->show();
        connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(showEditDialog()));
        connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(removeWork()));
        ui->addBtn->setText("Изменить");
    }
    else {
        ui->addBtn->hide();
        ui->deleteBtn->hide();
    }
    ui->date->setReadOnly(true);
    ui->desc->setReadOnly(true);
    ui->date->setText(date);
    ui->desc->setText(desc);
    this->setObjectName("_widget");
    qDebug() << this;
    this->setStyleSheet("#_widget {background-color: #FFCB00;}");
    //this->
}

WorksWidget::~WorksWidget()
{
    this->settings->close();
    //this->settings->deleteLater();
    delete settings;
    //disconnect(ui->dateBtn, SIGNAL(clicked()), this, SLOT(showCalendar()));
    delete ui;
}
