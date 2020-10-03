#include "dbmanager.h"
#include "deletecell.h"
#include "ui_deletecell.h"

DeleteCell::DeleteCell(QString requestId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteCell)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    this->requestId = requestId;
    connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(removeRequest()));
    ui->deleteBtn->setIcon(QIcon("del.png"));
}


DeleteCell::~DeleteCell()
{
    delete ui;
}


void DeleteCell::removeRequest()
{
    if(DBManager::instance()->removeRequest(requestId) == 1)
        emit deleted();
}

