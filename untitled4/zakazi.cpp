#include "zakazi.h"
#include "ui_zakazi.h"

zakazi::zakazi(QWidget *parent,mainww* m_parent) ://,mainww* m_parent
    QDialog(parent),
    ui(new Ui::zakazi)
{
    ui->setupUi(this);
    m = parent;
    m_parentt= m_parent;
    zakaz a[20];
    for (int i = 0; i < 20; i++) {
            QString z = "Имя - " + a[i].name + " | Фамилия - " + a[i].surname + " | Улица - " + a[i].street + " | Дом - " + QString::number(a[i].num)+ " | Действие - " + a[i].action +".";
            ui->listWidget->addItem(z);
        }
}

zakazi::~zakazi()
{
    delete ui;
}

void zakazi::on_pushButton_2_clicked()
{
    updateList();
}
void zakazi::updateList()
{
    ui->listWidget->clear();
    zakaz a[20];
    for (int i = 0; i < 20; i++) {
        QString z = "Имя - " + a[i].name + " | Фамилия - " + a[i].surname + " | Улица - " + a[i].street + " | Дом - " + QString::number(a[i].num)+ " | Действие - " + a[i].action +".";
        ui->listWidget->addItem(z);
    }
}

void zakazi::on_pushButton_clicked()
{
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();
    if (selectedItem) {
            QString zz = selectedItem->text();
            close();
            window3 = new currentzakaz(zz,m,m_parentt);
            window3->show();
        }
}

