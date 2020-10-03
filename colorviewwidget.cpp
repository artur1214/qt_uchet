#include "colorviewwidget.h"

#include <qcolordialog.h>

ColorViewWidget::ColorViewWidget(QString id, QString hex, QWidget *parent) : QWidget(parent)
{
    this->id = id;
    this->hex = hex;
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->setMinimumSize(50, 50);

    this->setStyleSheet("QWidget { background-color: " + hex + " ; border: 1px solid black;}");
    //this->setBackgroundRole(QPalette::Background);
}

void ColorViewWidget::setColor(QString hexColor)
{
    this->hex = hexColor;
    setStyleSheet("QWidget { background-color: " + hex + " ; border: 1px solid black;}");
}


void ColorViewWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    QColor color = QColorDialog::getColor(Qt::red, this);
    if ( color.isValid() ){
        setColor(color.name());
    }
    emit activated();
}
