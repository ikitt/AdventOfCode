#ifndef Y21DAY02_H
#define Y21DAY02_H

#include <QString>
#include <QVector>
#include <QDateTime>

class Y21Day02
{
public:
    Y21Day02();

    static void computFirstResult();
    static void computSecondResult();

private:
    static const QVector<int> _input;
};

#endif // Y21DAY02_H
