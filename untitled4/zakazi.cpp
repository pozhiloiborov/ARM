#include "zakazi.h"
#include "ui_zakazi.h"

zakazi::zakazi(QWidget *parent, mainww* p) :
    QDialog(parent),
    ui(new Ui::zakazi)
{
    ui->setupUi(this);
    pparent = p;
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
            pparent->show();
            pparent->take_zakaz(zz);
            pparent->addToCurrentList();
            close();
        }
}

