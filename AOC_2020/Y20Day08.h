#ifndef Y20DAY08_H
#define Y20DAY08_H

#include <QStringList>

class Y20Day08
{
public:
    Y20Day08();

    static int computFirstResult();
    static int computSecondResult();

private:
    static const QStringList _input;
    static int _accumulator;

    static void resetAccumulator();
    static int runSequence(QStringList input = {});
};

#endif // Y20DAY08_H
