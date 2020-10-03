#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
    ui->label_3->setText("");
    ui->passInp->setMaxLength(30);
    ui->loginInp->setMaxLength(25);
    connect(ui->checkBox, SIGNAL(stateChanged(int)), SLOT(showPass(int)));
    connect(ui->cancelBtn, SIGNAL( clicked() ), SLOT( reject() ) );
    connect(ui->okBtn, SIGNAL( clicked() ), SLOT( tryLogin() ) );
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::showPass(int state){
    if(state == Qt::Unchecked)
        ui->passInp->setEchoMode(QLineEdit::Password);
    else
        ui->passInp->setEchoMode(QLineEdit::Normal);

}

void LoginDialog::tryLogin()
{
    if(DBManager::instance()->login(getLogin(), getPass())){
        accept();
    }
    else{
        ui->label_3->setText("Ошибка, не верный логин или пароль");
        ui->passInp->setText("");
    }
}

QString LoginDialog::getLogin(){
    return ui->loginInp->text();
}


QString LoginDialog::getPass(){
    return ui->passInp->text();
}

