#ifndef Y20DAY09_H
#define Y20DAY09_H

#include <QVector>
#include <algorithm>

class Y20Day09
{
public:
    Y20Day09();

    static int computFirstResult();
    static int computSecondResult();

private:
    static const QVector<long long> _input;
    static const int preambleSize;

    static bool isOk(int inputIdx);
};

#endif // Y20DAY09_H
