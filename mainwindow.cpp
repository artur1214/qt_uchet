#include "dbmanager.h"
#include "logindialog.h"
#include "devicetypedialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workswidget.h"
#include "workcellwidget.h"
#include "addrequestform.h"
#include "deletecell.h"
#include "work.h"
#include "statusmanager.h"

#include <QCalendarWidget>
#include <QGridLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->db = DBManager::instance();
    ui->setupUi(this);
    connect(ui->statusManager, SIGNAL(triggered(bool)), SLOT(showStatusManager()));
    connect(ui->leaveAction, SIGNAL(triggered(bool)), SLOT(exitProgram()));
    connect(ui->reloadAction, SIGNAL(triggered(bool)), SLOT(showRequests()));
    connect(ui->addRequestBtn, SIGNAL(clicked()), this, SLOT(addRequest()));
    connect(ui->requestsTable->horizontalHeader(), SIGNAL( sectionResized(int, int, int) ), SLOT( resizeRequests(int, int, int) ) );
    connect(ui->requestsTable->verticalHeader(), SIGNAL( sectionResized(int, int, int) ), SLOT( onRowResize(int, int, int) ) );
    connect(ui->displayWorksAsBlock, SIGNAL(triggered(bool)), SLOT(setWorksDisplayTypeBlock()));
    connect(ui->displayWorksAsStrings, SIGNAL(triggered(bool)), SLOT(setWorksDisplayTypeString()));

    if(!showLoginDialog())
        AppSettings::curUser = "1";
        //exit(0);
    qDebug() << "привет юзер " << AppSettings::curUser;
    ui->requestsTable->setColumnCount(7);
    this->showRequests();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeRequests(int logicalIndex, int oldSize, int newSize)
{
    if(logicalIndex == 5){
        for (int i = 0; i< ui->requestsTable->rowCount(); i++) {
            ui->requestsTable->setRowHeight(i, ui->requestsTable->cellWidget(i, 5)->minimumHeight());
        }
    }
    if(ui->requestsTable->columnWidth(5) <= 260 && logicalIndex !=5 && logicalIndex!=3){
        qDebug() << logicalIndex;
        //ui->requestsTable->horizontalHeader()->resizeSection(logicalIndex, ui->requestsTable->horizontalHeader()->sectionSize(logicalIndex) -1);
    }
    //this->resized = true;
}


void MainWindow::resizeRequests()
{
    for (int i = 0; i< ui->requestsTable->rowCount(); i++) {
        ui->requestsTable->setRowHeight(i, ui->requestsTable->cellWidget(i, 5)->minimumHeight());
    }
}

void MainWindow::exitProgram()
{
    this->close();
    //exit(0);
}

void MainWindow::showRequests()
{
    ui->requestsTable->setWordWrap(true);
    ui->requestsTable->setAlternatingRowColors(true);
    ui->requestsTable->setRowCount(0);
    this->lastQueries = db->getAllRequests();
    for (int i = 0; i < lastQueries.length(); i++) {
        ui->requestsTable->insertRow(i);
        ui->requestsTable->setItem(i, 0, this->lastQueries[i].id);
        ui->requestsTable->setItem(i, 1, this->lastQueries[i].user);
        ui->requestsTable->setItem(i, 2, this->lastQueries[i].date);
        ui->requestsTable->setItem(i, 3, this->lastQueries[i].model);
        ui->requestsTable->setItem(i, 4, this->lastQueries[i].problem);

        WorkCellWidget* worksTableWidget = new WorkCellWidget(nullptr, lastQueries[i].works, lastQueries[i].id->text(), displayWorksType, lastQueries[i].status.color);
        //worksTableWidget->setStyleSheet(".QWidget{background-color: " + lastQueries[i].status.color + "; }");
        ui->requestsTable->setCellWidget(i, 5, worksTableWidget);
        //ui->requestsTable->item(i, 5)->setBackground(Qt::red);
        connect(worksTableWidget, SIGNAL(deleted()), SLOT(showRequests()));
        worksTableWidget->setObjectName("_widget");
        qDebug() << this;
        worksTableWidget->setStyleSheet("#_widget {background-color: #FFCB00 ;}");
        DeleteCell *del = new DeleteCell(this->lastQueries[i].id->text());
        del->setMaximumWidth(50);

        connect(del, SIGNAL(deleted()), this, SLOT(showRequests()));
        ui->requestsTable->setCellWidget(i, 6, del);
       // this->setStyleSheet("QTableWidget::cell{background-color: #ABA4C2; border: 1px, solid black; }");

        ui->requestsTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
        ui->requestsTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    }

    //ui->requestsTable->horizontalHeader()->setMinimumSectionSize(240);
    QStringList headers;
    headers << "id" << "Клиент" << "Дата обращения" << "Описание Проблемы" << "Устройство"<< "Выполненные работы" <<"Удалить";
    ui->requestsTable->setHorizontalHeaderLabels(headers);
    ui->requestsTable->horizontalHeader()->resizeSection(6, 60);
    //ui->requestsTable->horizontalHeader()->setStretchLastSection(true);
    resizeRequests();
}

bool MainWindow::addRequest()
{
    AddRequestForm deviceAddForm(this);
    switch(deviceAddForm.exec()) {
    case QDialog::Accepted:
        showRequests();
        return true;
    case QDialog::Rejected:
        return false;
    default:
        qDebug() << "Unexpected";
        return false;
    }
}

void MainWindow::setWorksDisplayTypeBlock()
{
    if(displayWorksType != AppSettings::Block){
        displayWorksType = AppSettings::DisplayWorksTypes::Block;
        showRequests();
    }

}

void MainWindow::setWorksDisplayTypeString()
{
    if(displayWorksType != AppSettings::String){
        displayWorksType = AppSettings::String;
        showRequests();
    }
}


void MainWindow::onRowResize(int logicalIndex, int oldSize, int newSize)
{
    int min = ui->requestsTable->cellWidget(logicalIndex, 5)->minimumHeight();
    if(min > newSize){
        ui->requestsTable->setRowHeight(logicalIndex, min);
    }
}

void MainWindow::showStatusManager()
{
    StatusManager *manager = new StatusManager();
    manager->show();
    manager->setAttribute(Qt::WA_DeleteOnClose);

}

QString MainWindow::getCurUserId() const
{
    return curUserId;
}

void MainWindow::setCurUserId(const QString &value)
{
    curUserId = value;
}

int MainWindow::getDisplayWorksType() const
{
    return displayWorksType;
}

void MainWindow::setDisplayWorksType(int value)
{
    displayWorksType = value;
}


bool MainWindow::showLoginDialog(){
    LoginDialog loginForm(this);
    switch(loginForm.exec()) {
    case QDialog::Accepted:
        return true;
    case QDialog::Rejected:
        return false;
    default:
        qDebug() << "Unexpected";
        return false;
    }


}
