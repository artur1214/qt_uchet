#ifndef DELETECELL_H
#define DELETECELL_H

#include <QWidget>

namespace Ui {
class DeleteCell;
}

class DeleteCell : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteCell(QString requestId, QWidget *parent = nullptr);
    ~DeleteCell();

private slots:
    void removeRequest();
signals:
    void deleted();
private:
    QString requestId;
    Ui::DeleteCell *ui;
};

#endif // DELETECELL_H
