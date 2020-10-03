#ifndef STATUSSUBVIEW_H
#define STATUSSUBVIEW_H

#include <QWidget>

namespace Ui {
class StatusSubView;
}

class StatusSubView : public QWidget
{
    Q_OBJECT

public:
    explicit StatusSubView(QString id, QString desc, QString hexColor, QWidget *parent = nullptr);
    ~StatusSubView();

private:
    QString id, desc, hexColor;
    Ui::StatusSubView *ui;
};

#endif // STATUSSUBVIEW_H
