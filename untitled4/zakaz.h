#ifndef ZAKAZ_H
#define ZAKAZ_H
#include <time.h>
#include <QStringList>
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
        QStringList names = {"Сергей", "Андрей", "Владимир", "Артём", "Влад", "Данил", "Алексей","Игорь","Фёдор","Томас","Фома","Виткор","Миктор","Фридрих","Данияр","Никита","Илья","Евгений","Аристарх","Дмитрий","Михаил","Максим"};
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
#endif // ZAKAZ_H
