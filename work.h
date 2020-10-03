#ifndef WORK_H
#define WORK_H

#include <QWidget>

namespace Ui {
class Work;
}

class Work : public QWidget
{
    Q_OBJECT

public:
    explicit Work(QString date, QString desc, QString id, QString user, QWidget *parent = nullptr);
    ~Work();
    QString requestId;
    QString id;

protected:
    void mouseDoubleClickEvent(QMouseEvent *);
signals:
    void deleted();
private slots:
    void removeWork();

private:
    bool editable;
    Ui::Work *ui;
};

#endif // WORK_H
