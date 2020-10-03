#include "colorviewform.h"
#include "ui_colorviewform.h"

#include <QStyle>
#include <qcolordialog.h>

ColorViewForm::ColorViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorViewForm)
{
    //this->id = id;
    ui->setupUi(this);
    this->hex = "#FAFAAA";
    //setMinimumSize(100, 100);
    this->setStyleSheet( ".QWidget { background-color: " + hex + " ; border: 1px solid black;}");
}

QString ColorViewForm::getColor()
{
    return this->hex;
}

ColorViewForm::ColorViewForm(QString id, QString hex, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorViewForm)
{
    ui->setupUi(this);
    this->id = id;
    this->hex = hex;
    //this->objectName();
    //QStyle *s = new QStyle();
    this->setObjectName("this");
    //this->setProperty("ColorViewWidget", true );
    this->setStyleSheet( ".QWidget { background-color: " + hex + " ; border: 1px solid black;}");
    //this->setStyleSheet( "QWidget QColorDialog { background-color: " + hex + " ; border: 1px solid black;}");
}

ColorViewForm::~ColorViewForm()
{
    delete ui;
}


void ColorViewForm::setColor(QString hexColor)
{
    this->hex = hexColor;
    setStyleSheet(".QWidget { background-color: " + hex + " ; border: 1px solid black;}");
}


void ColorViewForm::mouseDoubleClickEvent(QMouseEvent *)
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if ( color.isValid() ){
        setColor(color.name());
    }
    //emit activated();
}
