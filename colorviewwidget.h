#ifndef COLORVIEWWIDGET_H
#define COLORVIEWWIDGET_H

#include <QWidget>

class ColorViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorViewWidget(QString id, QString hex, QWidget *parent = nullptr);
    ColorViewWidget(QWidget *parent = nullptr);
signals:
    void activated();
public slots:
    void setColor(QString hexColor);

protected:
    void mouseDoubleClickEvent(QMouseEvent *);
private:
    QString id, hex;
};


#endif // COLORVIEWWIDGET_H
