#include "currentzakaz.h"
#include "ui_currentzakaz.h"

currentzakaz::currentzakaz(const QString& zz,QWidget *parent,mainww* m_parent) :
    QDialog(parent),
    ui(new Ui::currentzakaz)
{
    ui->setupUi(this);
    ui->label->setText(zz);
    mm=parent;
    m_parentt = m_parent;
}

currentzakaz::~currentzakaz()
{
    delete ui;
}

void currentzakaz::on_pushButton_clicked()
{
    close();
    mm->show();
    m_parentt->change_count("1");
    QString zz = ui->label->text();
    m_parentt->zakazinfo(zz);
}


void currentzakaz::on_pushButton_2_clicked()
{
    close();
    mm->show();
    m_parentt->change_count("0");
}

