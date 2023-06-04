#ifndef LISTCURR_H
#define LISTCURR_H

#include <QDialog>
#include "currentzakaz.h"
class currentzakaz;
namespace Ui {
class listcurr;
}

class listcurr : public QDialog
{
    Q_OBJECT

public:
    explicit listcurr(QWidget *parent = nullptr);
    ~listcurr();
public slots:
    void addToCurrList(QList<QString>  currentListt);
private slots:
    void on_pushButton_clicked();
    void backToMainww();
    void on_pushButton_2_clicked();

private:
    Ui::listcurr *ui;
    QString zz;
    QList<QString> currentList;
    currentzakaz* currentzakaz;
};

#endif // LISTCURR_H
