#include "mainww.h"
#include "ui_mainww.h"
#include <QPixmap>
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
    window2= new zakazi(this,this);//,this
    window2->show();
}
void mainww::change_count(QString s)
{
    if  ( s == "1")
    {
        QString temp = ui->count->text();
        int ss = temp.toInt();
        ss += 1;
        temp = QString::number(ss);
        ui->count->setText(temp);
    }
    if ( s=="0")
    {
        QString temp = ui->count1->text();
        int ss = temp.toInt();
        ss += 1;
        temp = QString::number(ss);
        ui->count1->setText(temp);
    }
}
void mainww::zakazinfo(QString z )
{
    zz = z;
    if (zz!=""){ completedList.append(zz);
    zz="";}
}

