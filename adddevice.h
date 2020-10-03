#ifndef ADDDEVICE_H
#define ADDDEVICE_H

#include "dbmanager.h"


#include <QDialog>

namespace Ui {
class AddDevice;
}

class AddDevice : public QDialog
{
    Q_OBJECT

public:
    explicit AddDevice(DBManager::DeviceType type, QWidget *parent = nullptr);
    ~AddDevice();

private slots:
    void addDevice();
private:
    DBManager::DeviceType deviceType;
    Ui::AddDevice *ui;
};

#endif // ADDDEVICE_H
