#ifndef ZAKAZI_H
#define ZAKAZI_H
#include <QDialog>
#include "zakaz.h"
#include "mainww.h"
class mainww;
namespace Ui {
class zakazi;
}

class zakazi : public QDialog
{
    Q_OBJECT

public:
    explicit zakazi(QWidget *parent = nullptr,mainww* p=nullptr);
    ~zakazi();

private slots:
    void on_pushButton_2_clicked();
    void updateList();
    void on_pushButton_clicked();

private:
    Ui::zakazi *ui;
    mainww* pparent;
};

#endif // ZAKAZI_H
