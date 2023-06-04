#include "listcurr.h"
#include "ui_listcurr.h"

listcurr::listcurr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listcurr)
{
    ui->setupUi(this);
}

listcurr::~listcurr()
{
    delete ui;
}
void listcurr::backToMainww()
{
    parentWidget()->show();
    hide();
}
void listcurr::addToCurrList(QList<QString>  currentListt)
{
    ui->list->clear();
    currentList = currentListt;
    for (const QString& item : currentList)
            ui->list->addItem(item);
}
void listcurr::on_pushButton_clicked()
{
    backToMainww();
}


void listcurr::on_pushButton_2_clicked()
{
    QListWidgetItem* selectedItem = ui->list->currentItem();
    if (selectedItem) {
           QString zz = selectedItem->text();

           pparent->show();
           pparent->take_zakaz(zz);
           close();
    }
}

