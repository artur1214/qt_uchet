#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbmanager.h"
#include "logindialog.h"
#include "appsettings.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getDisplayWorksType() const;
    void setDisplayWorksType(int value);


    QString getCurUserId() const;
    void setCurUserId(const QString &value);

private slots:
    void resizeRequests(int logicalIndex, int oldSize, int newSize);
    void resizeRequests();
    void exitProgram();
    void showRequests();
    bool addRequest();
    void setWorksDisplayTypeBlock();
    void setWorksDisplayTypeString();
    void onRowResize(int, int, int);
    void showStatusManager();
    //void removeRequest(QString id);

private:
    QString curUserId = "1";
    int displayWorksType = AppSettings::DisplayWorksTypes::Block;
    QList<int> headerSizes;
    bool resized = false;
    QList<DBManager::RequestsQuerryRes> lastQueries;

    //LoginDialog loginForm;
    bool addDeviceType();
    Ui::MainWindow *ui;
    DBManager* db = nullptr;
    bool showLoginDialog();
};

#endif // MAINWINDOW_H
