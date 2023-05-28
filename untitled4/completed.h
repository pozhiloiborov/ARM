#ifndef COMPLETED_H
#define COMPLETED_H

#include <QDialog>
#include "mainww.h"
namespace Ui {
class completed;
}

class completed : public QDialog
{
    Q_OBJECT

public:
    explicit completed(QWidget *parent = nullptr);
    ~completed();

private slots:
    void backToMainww();
    void on_pushButton_clicked();

public slots:
    void addToCompletedList(QList<QString>  completedListt);
private:
    Ui::completed *ui;
    QString zz;
    QList<QString> completedList;
};
#endif // COMPLETED_H
