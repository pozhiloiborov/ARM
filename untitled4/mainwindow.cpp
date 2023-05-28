#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QString surname = ui->lineEdit_2->text();
    if (name== "") QMessageBox::critical(this,"Ошибка","Имя не введено");
    else if (surname== "") QMessageBox::critical(this,"Ошибка","Фамилия не введена");
    else{
        close();
        window1= new mainww(name,surname,this);
        window1->show();
    }
}

