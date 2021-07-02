#ifndef Y20DAY15_H
#define Y20DAY15_H


#include <QVector>
#include <QMap>
#include <QDateTime>

class Y20Day15
{
public:
    Y20Day15();

    static int computFirstResult();
    static unsigned long long int computSecondResult();
    static unsigned long long int computSecondResultBasicAndSlow();
    static unsigned long long int computSecondResultMessUp();


private:
    static const QVector<int> _input;
};

#endif // Y20DAY15_H
