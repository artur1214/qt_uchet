#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include <QWidget>
#include <appsettings.h>
namespace Ui {
class StatusManager;
}

class StatusManager : public QWidget
{
    Q_OBJECT

public:
    explicit StatusManager(QWidget *parent = nullptr);
    ~StatusManager();

private slots:
    bool addStatus();
    void updateStatuses();

private:
    QList<AppSettings::RequestStatus> statuses;
    Ui::StatusManager *ui;
};

#endif // STATUSMANAGER_H
