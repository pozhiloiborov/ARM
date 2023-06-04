#include "mainww.h"
#include "ui_mainww.h"
#include <QPixmap>
int n=4;
int m=2;
mainww::mainww(const QString& name, const QString& surname,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainww),
    completedWindow(nullptr)
{
    ui->setupUi(this);
    ui->name->setText(name);
    ui->surname->setText(surname);
    QPixmap pix(":/img/image/anonim.png");
    int w =400;
    int h =400;
    ui->pic->setPixmap(pix.scaled(w,h));
    ui->widget->xAxis->setRange(0,n);
    ui->widget->yAxis->setRange(0,m);
    ui->widget->xAxis->setLabel("Всего заказов");
    ui->widget->yAxis->setLabel("Успешные заказы");
    QFont labelFont("Arial", 15);
    ui->widget->xAxis->setLabelFont(labelFont);
    ui->widget->yAxis->setLabelFont(labelFont);
    x.push_back(0);
    y.push_back(0);
}

mainww::~mainww()
{
    delete ui;
}

void mainww::openCompleted()
{
    if (!completedWindow)
       {
           completedWindow = new completed(this);
       }
       completedWindow->show();
       this->hide();
       completedZakaz(completedList);
}
void mainww::completedZakaz(QList<QString> completedList)
{
    if (completedWindow)
    {
        completedWindow->addToCompletedList(completedList);
    }
}
void mainww::on_pushButton_2_clicked()
{
    openCompleted();
}
void mainww::on_pushButton_clicked()
{
    hide();
    window2= new zakazi(this,this);
    window2->show();
}
void mainww::change_count(QString s)
{
    if  ( s == "1")
    {
        success +=1;
        QString temp = QString::number(success);
        ui->count->setText(temp);
    }
    if ( s=="0")
    {
        fail +=1;
        QString temp = QString::number(fail);
        ui->count1->setText(temp);
    }
    x.push_back(success+fail);
    y.push_back(success);
    graph();
}
void mainww::zakazinfo(QString z )
{
    zz = z;
    if (zz!=""){ completedList.append(zz);
    zz="";}
}
void mainww::graph()
{
    if (n<=(success + fail)) n+=1;
    if (m<=success) m+=1;
    ui->widget->xAxis->setRange(0,n);
    ui->widget->yAxis->setRange(0,m);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();
}
void mainww::take_zakaz(QString zakaz)
{
    currentList.append(zakaz);
}
void mainww::on_pushButton_3_clicked()
{
    QListWidgetItem* selectedItem = ui->list->currentItem();
    if (selectedItem) {
            QString temp = selectedItem->text();
            ui->list->takeItem(ui->list->row(selectedItem));
            delete selectedItem;
            currentList.removeOne(temp);
            window3= new currentzakaz(this,temp,this);
            window3->show();
            hide();
        }
}
void mainww::addToCurrentList()
{
    ui->list->clear();
    for (const QString& item : currentList)
            ui->list->addItem(item);
}

