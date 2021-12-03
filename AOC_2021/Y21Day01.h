#ifndef Y21DAY01_H
#define Y21DAY01_H

#include <QString>
#include <QVector>
#include <QDateTime>

class Y21Day01
{
public:
    Y21Day01();

    static void computFirstResult();
    static void computSecondResult();

private:
    static const QVector<QString> _input;
};

#endif // Y21DAY01_H
