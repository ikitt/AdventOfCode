#ifndef Y21DAY06_H
#define Y21DAY06_H

#include <QString>
#include <QVector>

class Y21Day06
{
public:
    Y21Day06();

    static void computFirstResult();
    static void computSecondResult();




private:
    static const QString _input;
    static QVector<unsigned long long int> _population;

    static void readInput();
    static void printPop();
};

#endif // Y21DAY06_H
