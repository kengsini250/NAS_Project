#include "newuser.h"
#include "ui_newuser.h"

NewUser::NewUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUser)
{
    ui->setupUi(this);
    ui->lineEdit->setText("oppai@192.168.2.46");
    connect(ui->buttonBox,&QDialogButtonBox::accepted,[this]{
        emit send(ui->lineEdit->text());
    });
}

NewUser::~NewUser()
{
    delete ui;
}
