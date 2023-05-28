#ifndef MAINWW_H
#define MAINWW_H

#include <QDialog>
#include "zakazi.h"
#include "completed.h"
#include "currentzakaz.h"
class zakazi; // Предварительное объявление класса zakazi
class currentzakaz; // Предварительное объявление класса currentzakaz
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

public slots:
    void zakazinfo(QString z);
    void change_count(QString h);
    void completedZakaz(QList<QString> completedList );
private:
    zakazi* window2;
    Ui::mainww *ui;
    QString zz;
    QString h;
    completed*  completedWindow;
    QList<QString> completedList;
};

#endif // MAINWW_H
