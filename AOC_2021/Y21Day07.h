#ifndef Y21DAY07_H
#define Y21DAY07_H

#include <QString>
#include <QVector>


class Y21Day07
{
public:
    Y21Day07();

    static void computFirstResult();
    static void computSecondResult();



private:
    static const QString _input;
    static unsigned long long int _maxPos;
    static QVector<unsigned long long int> _initPos;
    static QVector<unsigned long long int> _fuelCost;

    static void readInput();
    static void computeCostByPos();
    static void computeCostByPosWithSum();
    static unsigned long long int getMinCost();
    static unsigned long long int sumTo(unsigned long long int n);
};

#endif // Y21DAY07_H
