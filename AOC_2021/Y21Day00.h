#ifndef Y21DAY00_H
#define Y21DAY00_H

#include <QString>
#include <QVector>

class Y21Day00
{
public:
    Y21Day00();

    static void computFirstResult();
    static void computSecondResult();



private:
    static const QVector<QString> _input;
};

#endif // Y21DAY00_H
