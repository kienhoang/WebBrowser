#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}
QString SettingDialog::gethomepage(){
    return ui->leHomepage->text();
}

void SettingDialog::on_pushButton_clicked()
{
    this->close();
}
void SettingDialog::setcrnthomepage(QString s){
    ui->leHomepage->setText(s);
}
