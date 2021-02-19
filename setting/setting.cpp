#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    ui->lineEdit->setText("C:\\Users\\kengs\\Desktop\\");
    connect(ui->buttonBox,&QDialogButtonBox::accepted,[this]{
        emit send(ui->lineEdit->text());
    });
}

Setting::~Setting()
{
    delete ui;
}
