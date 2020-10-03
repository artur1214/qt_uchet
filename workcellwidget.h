#ifndef WORKCELLWIDGET_H
#define WORKCELLWIDGET_H

#include "appsettings.h"
#include "dbmanager.h"
#include "workswidget.h"

#include <QWidget>

namespace Ui {
class WorkCellWidget;
}

class WorkCellWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WorkCellWidget(QWidget *parent);
    explicit WorkCellWidget(QWidget *parent = nullptr, QList<DBManager::Work> works = QList<DBManager::Work>(), QString requestId = "", int displayType = AppSettings::DisplayWorksTypes::Block, QString status = "");
    ~WorkCellWidget();

signals:
    void deleted();

protected:
    QString requestId;
    virtual void resizeEvent(QResizeEvent *event);
    //QList<QStringList> lastWorks;
    int curColCount;
    QList<QWidget *> works;

private slots:
    void removeRequest();
    void addWork();
    void onDelete();
    //void saveWork();

private:
    int displayType;
    Ui::WorkCellWidget *ui;
};

#endif // WORKCELLWIDGET_H
