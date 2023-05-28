#ifndef ZAKAZI_H
#define ZAKAZI_H
#include <QDialog>
#include <QStringList>
#include <time.h>
#include "mainww.h"
#include "currentzakaz.h"
class currentzakaz;
class mainww;
namespace Ui {
class zakazi;
}

class zakaz
{
public:
    QString name;
    QString surname;
    QString street;
    QString action;
    int num;

public:
    zakaz()
    {
        QStringList names = {"Сергей", "Андрей", "Владимир", "Артём", "Влад", "Данил", "Алексей","Анна","Елизавета","Александра","Маргарита","Татьяна","Элеонора","Полина","Данияр","Никита","Илья","Евгений","Евгения","Дмитрий","Михаил","Максим"};
        QStringList surnames = {"Александров", "Алексеев", "Андреев", "Данилов", "Артёмов", "Сергеев","Агибалов","Абрамкин","Прокофьев","Пушкин","Гайдар","Ленин","Сталин","Юков","Некрасов","Гоголь","Путин","Песков","Лядов"};
        QStringList streets = {"Пушкина", "Попова", "Пермская", "Акулова", "Ленина", "Героев Хасана", "Луначарского","Авиационная","Грибная","Сибирская","Шоссе Косманавтов","Куйбышева","Карпинского","9 мая","Яблочкова","Старцева","Кочегаров"};
        QStringList actions = {"Покупка","Продажа","Консультация","Осмотр и оценка жилья"};
        int x = rand() % names.size();
        int y = rand() % surnames.size();
        int z = rand() % streets.size();
        int v = rand() % 250;
        int w = rand()% actions.size();
        name = names[x];
        surname = surnames[y];
        street = streets[z];
        num = v;
        action =  actions[w];
    }
};

class zakazi : public QDialog
{
    Q_OBJECT

public:
    explicit zakazi(QWidget *parent = nullptr,mainww*  m_parent = nullptr);//,mainww* m_parent
    ~zakazi();

private slots:
    void on_pushButton_2_clicked();
    void updateList();
    void on_pushButton_clicked();

private:
    Ui::zakazi *ui;
    currentzakaz * window3;
    QWidget* m;
    mainww* m_parentt;
};

#endif // ZAKAZI_H
