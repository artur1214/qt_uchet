#ifndef COLORVIEWFORM_H
#define COLORVIEWFORM_H

#include <QWidget>

namespace Ui {
class ColorViewForm;
}

class ColorViewForm : public QWidget
{
    Q_OBJECT

public:
    QString getColor();
    explicit ColorViewForm(QString id, QString hex, QWidget *parent = nullptr);
    explicit ColorViewForm(QWidget *parent = nullptr);
    ~ColorViewForm();

protected:
    void mouseDoubleClickEvent(QMouseEvent *);
private slots:
    void setColor(QString hexColor);
private:
    QString id, hex;
    Ui::ColorViewForm *ui;
};

#endif // COLORVIEWFORM_H
