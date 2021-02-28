#include "newuser.h"
#include "ui_newuser.h"

NewUser::NewUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUser)
{
    ui->setupUi(this);
    ui->user->setText("oppai");
    ui->address->setText("192.168.2.46");
    connect(ui->buttonBox,&QDialogButtonBox::accepted,[this]{
        emit send(User{ui->user->text(),ui->address->text()});
    });
}

NewUser::~NewUser()
{
    delete ui;
}
