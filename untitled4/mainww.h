#ifndef MAINWW_H
#define MAINWW_H

#include <QDialog>
#include "zakazi.h"
#include "completed.h"
#include "currentzakaz.h"
#include <QVector>
class zakazi;
class currentzakaz;
class completed;
namespace Ui {
class mainww;
}

class mainww : public QDialog
{
    Q_OBJECT

public:
    explicit mainww(const QString& name, const QString& surname,QWidget *parent = nullptr);
    ~mainww();
private slots:
    void openCompleted();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
public slots:
    void zakazinfo(QString z);
    void change_count(QString h);
    void completedZakaz(QList<QString> completedList );
    void graph();
    void take_zakaz(QString zakaz);
    void addToCurrentList();
private:
    zakazi* window2;
    Ui::mainww *ui;
    QString zz;
    QString h;
    completed*  completedWindow;
    QList<QString> completedList;
    QList<QString> currentList;
    currentzakaz* window3;
    int fail=0;
    int success=0;
    QVector<double> x,y;
};

#endif // MAINWW_H
