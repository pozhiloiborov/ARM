#include "completed.h"
#include "ui_completed.h"
completed::completed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::completed)
{
    ui->setupUi(this);
}

completed::~completed()
{
    delete ui;
}
void completed::backToMainww()
{
    parentWidget()->show();
    hide();
}

void completed::addToCompletedList(QList<QString> completedListt)
{
    ui->list->clear();
    completedList = completedListt;
    for (const QString& item : completedList)
            ui->list->addItem(item);
}
void completed::on_pushButton_clicked()
{
    backToMainww();
}

