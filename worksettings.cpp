#include "worksettings.h"
#include "ui_worksettings.h"

#include <QtDebug>



WorkSettings::WorkSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkSettings)
{
    //setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(saveSettings()));
}

WorkSettings::~WorkSettings()
{

    delete ui;
}

void WorkSettings::saveSettings()
{
    this->date = ui->calendar->selectedDate();
    this->close();

    //qDebug() << "Нажато!";
    //this->close();
}


void WorkSettings::closeEvent(QCloseEvent *event)
{
      emit WidgetClosed();
}
