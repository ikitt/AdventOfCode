#ifndef Y20DAY03_H
#define Y20DAY03_H


#include <QString>
#include <QStringList>
#include <QList>

class Y20Day03
{
public:
    Y20Day03();

    static int computFirstResult();
    static long long int computSecondResult();


private:

    static int computeSlope(int plus_x, int plus_y);

    static const QString _tree;
    static const QString _snow;
    static const QStringList _input;
};

#endif // Y20DAY03_H
