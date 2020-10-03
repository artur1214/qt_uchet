#ifndef ADDCLIENT_H
#define ADDCLIENT_H

#include <QDialog>

namespace Ui {
class AddClient;
}

class AddClient : public QDialog
{
    Q_OBJECT

private slots:
    void addClient();
public:
    explicit AddClient( QWidget *parent = nullptr);
    ~AddClient();

private:
    Ui::AddClient *ui;
};

#endif // ADDCLIENT_H
