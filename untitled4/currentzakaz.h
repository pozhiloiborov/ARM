#ifndef CURRENTZAKAZ_H
#define CURRENTZAKAZ_H

#include <QDialog>
#include "mainww.h"
class mainww;
namespace Ui {
class currentzakaz;
}

class currentzakaz : public QDialog
{
    Q_OBJECT

public:
    explicit currentzakaz(QWidget *parent = nullptr,const QString& name="",mainww* m_parent=nullptr);
    ~currentzakaz();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::currentzakaz *ui;
    mainww* m_parentt;
};

#endif // CURRENTZAKAZ_H
