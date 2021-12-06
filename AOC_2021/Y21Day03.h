#ifndef Y21DAY03_H
#define Y21DAY03_H

#include <QString>
#include <QVector>
#include <QDateTime>

class Y21Day03
{
public:
    Y21Day03();

    static void computFirstResult();
    static void computSecondResult();
    static char mostCommonChar(const QVector<QString> & input, int idx);

    static void getOx();
    static void getCo2();

    static int oxRatio;
    static int co2Ratio;

private:
    static const QVector<QString> _input;
};

#endif // Y21DAY03_H
