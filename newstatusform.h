#ifndef NEWSTATUSFORM_H
#define NEWSTATUSFORM_H

#include <QDialog>
#include <qcolordialog.h>

namespace Ui {
class NewStatusForm;
}

class NewStatusForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewStatusForm(QWidget *parent = nullptr);
    ~NewStatusForm();

private slots:
    void switchColor();
    void save();
private:
    Ui::NewStatusForm *ui;
    QColorDialog color;
};

#endif // NEWSTATUSFORM_H
