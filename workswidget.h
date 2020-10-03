#ifndef WORKSWIDGET_H
#define WORKSWIDGET_H

#include <QWidget>
#include "dbmanager.h"
#include "worksettings.h"
namespace Ui {
class WorksWidget;
}

class WorksWidget : public QWidget
{
    Q_OBJECT

private slots:
    void showCalendar();
    void saveWork();
    void showDate();
    void cancel();
    void removeWork();
    void editWork();
    void updateWork();
    void showEditDialog();
signals:
    void deleted();

public:
    explicit WorksWidget(QString requestId, QWidget *parent = nullptr);
    explicit WorksWidget(WorksWidget *parent);
    explicit WorksWidget(QString date, QString desc, QString id, QString user, QWidget *parent = nullptr );
    ~WorksWidget();
    QString requestId;
    QString id;
    QString curDate;
    QString curDesc;
    /*struct Work{
        QString id;
        QString date;
        QString description;
    };*/
private:
    WorksWidget *from;
    WorkSettings *settings;
    Ui::WorksWidget *ui;
};

#endif // WORKSWIDGET_H
