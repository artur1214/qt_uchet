#include "colorviewform.h"
#include "colorviewwidget.h"
#include "statussubview.h"
#include "ui_statussubview.h"

StatusSubView::StatusSubView(QString id, QString desc, QString hexColor, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusSubView)
{
    ui->setupUi(this);
    this->id = id;
    this->desc = desc;
    this->hexColor = hexColor;
    ui->label->setText(desc);
    ui->gridLayout->addWidget(new ColorViewForm(id,hexColor, this), 0, 1);
    //ui->color->setStyleSheet("QWidget { background-color: " + hexColor + ";}");
}

StatusSubView::~StatusSubView()
{
    delete ui;
}
