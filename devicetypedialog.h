#ifndef DEVICETYPEDIALOG_H
#define DEVICETYPEDIALOG_H

#include <QDialog>

namespace Ui {
class DeviceTypeDialog;
}

class DeviceTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceTypeDialog(QWidget *parent = nullptr);
    ~DeviceTypeDialog();

private slots:
    void addDeviceType();

private:
    Ui::DeviceTypeDialog *ui;
};

#endif // DEVICETYPEDIALOG_H
