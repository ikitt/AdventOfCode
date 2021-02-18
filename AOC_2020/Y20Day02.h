#ifndef Y20DAY02_H
#define Y20DAY02_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QRegularExpression>

class Y20Day02
{
public:
    Y20Day02();

    static int computFirstResult();
    static int computSecondResult();

private:
    static const QStringList _input;
};

#endif // Y20DAY02_H
