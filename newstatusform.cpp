#include "colorviewform.h"
#include "colorviewwidget.h"
#include "dbmanager.h"
#include "newstatusform.h"
#include "ui_newstatusform.h"

#include <QColorDialog>

NewStatusForm::NewStatusForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewStatusForm)
{
    ui->setupUi(this);
    //QColorDialog *color = new QColorDiathis);
    //connect(ui->ComboBox, SIGNAL( activated() ), SLOT( switchColor() ) );
    ui->color = new ColorViewForm(ui->color);
    //((ColorViewForm)(ui->color));
    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
}

NewStatusForm::~NewStatusForm()
{
    delete ui;
}

void NewStatusForm::switchColor()
{

}

void NewStatusForm::save()
{
    int res = DBManager::instance()->addStatus(ui->LineEdit->text(), ((ColorViewForm*)ui->color)->getColor());
    if(res == 1){
        qDebug() << "добавлен новый статус";
        accept();
    }
    else if(res == 20){
        ui->error->setText("Статус с таким цветом уже есть");
    }
    else if(res == 19){
        ui->error->setText("есть такое название");
    }

}
