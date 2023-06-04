#include "currentzakaz.h"
#include "ui_currentzakaz.h"

currentzakaz::currentzakaz(QWidget *parent,const QString& zz,mainww* m_parent) :
    QDialog(parent),
    ui(new Ui::currentzakaz)
{
    ui->setupUi(this);
    ui->label->setText(zz);
    m_parentt=m_parent;
}

currentzakaz::~currentzakaz()
{
    delete ui;
}

void currentzakaz::on_pushButton_clicked()
{
    m_parentt->change_count("1");
    QString zz = ui->label->text();
    m_parentt->zakazinfo(zz);
    m_parentt->show();
    close();
}


void currentzakaz::on_pushButton_2_clicked()
{
    m_parentt->change_count("0");
    m_parentt->show();
    close();
}

