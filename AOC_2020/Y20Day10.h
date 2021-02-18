#ifndef Y20DAY10_H
#define Y20DAY10_H

#include <QVector>
#include <QMap>

#include <algorithm>

class Y20Day10
{
public:
    Y20Day10();

    static int computFirstResult();
    static int computSecondResult();

private:
    static const QVector<int> _input;
    static const int preambleSize;

    static int countPossibility(const QVector<int> &nonThreeChain, int position = 1);

//    static bool isOk(int inputIdx);
};

#endif // Y20DAY10_H
