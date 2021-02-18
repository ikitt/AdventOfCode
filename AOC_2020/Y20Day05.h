#ifndef Y20DAY05_H
#define Y20DAY05_H

#include <cmath>

#include <QString>
#include <QStringList>
#include <QList>

class Y20Day05
{
public:
    Y20Day05();

    static int computFirstResult();
    static int computSecondResult();


private:
    static const QStringList _input;

    static bool getRowColumnId(QString seatStr, int& row, int& column, int& id);
};

#endif // Y20DAY05_H
