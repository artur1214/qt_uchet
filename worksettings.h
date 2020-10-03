#ifndef WORKSETTINGS_H
#define WORKSETTINGS_H

#include <QDate>
#include <QWidget>

namespace Ui {
class WorkSettings;
}

class WorkSettings : public QWidget
{
    Q_OBJECT

public:
    explicit WorkSettings(QWidget *parent = nullptr);
    ~WorkSettings();
    QDate date;
    QString requestId;
    virtual void closeEvent(QCloseEvent *event);
private slots:
    void saveSettings();

signals:
    void WidgetClosed();
protected:

private:
    Ui::WorkSettings *ui;
};

#endif // WORKSETTINGS_H
